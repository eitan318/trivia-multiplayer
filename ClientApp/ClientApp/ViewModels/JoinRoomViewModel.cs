using ClientApp.Commands;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Models;
using ClientApp.Services;
using System.Windows.Input;
using ClientApp.Stores;
using System.Collections.ObjectModel;

namespace ClientApp.ViewModels
{
    class JoinRoomViewModel : ViewModelBase
    {
        private RoomDataStore _roomDataStore;
        private readonly RequestsExchangeService _requestsExchangeService;
        private CancellationTokenSource _refreshRoomsCTS;
        private readonly int refreshMS = 300;

        public JoinRoomViewModel(
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService,
            RoomDataStore roomDataStore) : base(true)
        {
            this._requestsExchangeService = requestsExchangeService;
            this._roomDataStore = roomDataStore;
            JoinCmd = new JoinCommand(this, navigationService, requestsExchangeService, roomDataStore);
        }


        public override void OnNavigatedTo()
        {
            _refreshRoomsCTS = new CancellationTokenSource();
            Task.Run(() => PeriodicallyRefreshRooms(_refreshRoomsCTS.Token)); 
        }

        public override void OnNavigatedAway()
        {
            _refreshRoomsCTS?.Cancel();
            _refreshRoomsCTS?.Dispose();
        }

        // Commands
        public ICommand JoinCmd { get; }

        // Fields
        private List<RoomPreview> _rooms;
        private RoomPreview? _selectedRoom;
        private string _searchQuery;
        private ObservableCollection<RoomPreview> _filteredRooms;

        public ObservableCollection<RoomPreview> FilteredRooms
        {
            get => _filteredRooms;
            set
            {
                _filteredRooms = value;
                OnPropertyChanged();
            }
        }

        public string SearchQuery
        {
            get => _searchQuery;
            set
            {
                _searchQuery = value;
                OnPropertyChanged();
            }
        }


        // Error message fields
        private string _errorMessage;


        public RoomPreview? SelectedRoom
        {
            get => _selectedRoom;
            set
            {
                _selectedRoom = value;
                _roomDataStore.CurrentRoomData = value?.RoomData;
                OnPropertyChanged();
                // Notify JoinCommand that its state may have changed
                ((CommandBase)JoinCmd).RaiseCanExecuteChanged();
            }
        }

        public string ErrorMessage
        {
            get => _errorMessage;
            set
            {
                _errorMessage = value;
                OnPropertyChanged();
            }
        }

        private async Task PeriodicallyRefreshRooms(CancellationToken token)
        {
            try
            {
                while (!token.IsCancellationRequested)
                {
                    await Refresh();
                    await Task.Delay(refreshMS, token); // Pass the token to enable cancellation
                }
            }
            catch (OperationCanceledException)
            {
                // Task was canceled; no further action needed
            }
        }
          private void UpdateFilteredRooms()
          {
              if (string.IsNullOrWhiteSpace(SearchQuery))
              {
                  FilteredRooms = new ObservableCollection<RoomPreview>(_rooms);
              }
              else
              {
                  var lowerQuery = SearchQuery.ToLower();
                var filtered = _rooms
                  .Where(room => room.RoomData.Id.ToString().Contains(lowerQuery) ||
                                   room.RoomData.RoomName.ToLower().Contains(lowerQuery))
                    .ToList();
                  FilteredRooms = new ObservableCollection<RoomPreview>(filtered);
              }
          }


        public async Task Refresh()
        {
            try
            {
                var request = new GetRoomsRequest();
                var responseInfo = await _requestsExchangeService.ExchangeRequest<GetRoomsResponse>(request);

                App.Current.Dispatcher.Invoke(() =>
                {
                    if (responseInfo.NormalResponse)
                    {
                        var refreshedRooms = responseInfo.Response.Rooms;

                        var currentlySelectedRoomId = SelectedRoom?.RoomData.Id;
                        var matchingRoom = refreshedRooms.FirstOrDefault(r => r.RoomData.Id == currentlySelectedRoomId);

                        _rooms = refreshedRooms;

                        SelectedRoom = matchingRoom;
                        UpdateFilteredRooms();
                    }
                });
            }
            catch (Exception ex)
            {
                ErrorMessage = $"Error retrieving room list: {ex.Message}";
            }
        }


    }
}
