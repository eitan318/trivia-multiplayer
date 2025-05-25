using ClientApp.Commands;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Models;
using ClientApp.Services;
using ClientApp.ViewModels;
using System.Windows.Input;
using ClientApp.Stores;
using System.Printing;

namespace ClientApp.ViewModels
{

    class JoinRoomViewModel : ViewModelBase
    {
        private RoomDataStore _roomDataStore;
        private readonly RequestsExchangeService _requestsExchangeService;
        public JoinRoomViewModel(
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService,
            RoomDataStore roomDataStore) : base(true)
        {
            this._requestsExchangeService = requestsExchangeService;
            this._roomDataStore = roomDataStore;
            RefreshCmd = new RelayCommand(async () => await Refresh());
            JoinCmd = new JoinCommand(this, navigationService, requestsExchangeService, roomDataStore);
            _ = Refresh(); // Fire and forget
        }


        // Commands
        public ICommand RefreshCmd { get; }
        public ICommand JoinCmd { get; }


        // Fields
        private List<RoomPreview> _rooms;
        private RoomPreview? _selectedRoom;
        
        // Error message fields
        private string _errorMessage;


        //Properties
        public List<RoomPreview> Rooms
        {
            get => _rooms;
            set
            {
                _rooms = value;
                OnPropertyChanged();
            }
        }


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

        
        // Errore message properties
        public string ErrorMessage
        {
            get => _errorMessage;
            set
            {
                _errorMessage = value;
                OnPropertyChanged();
            }
        }





        public async Task Refresh()
        {
            try
            {
                var request = new GetRoomsRequest();
                var responseInfo = await _requestsExchangeService.ExchangeRequest<GetRoomsResponse>(request);

                if (responseInfo.NormalResponse)
                {
                    Rooms = responseInfo.Response.Rooms;

                    // Clear selection after refreshing to ensure consistency
                    SelectedRoom = null; 
                }
                else
                {
                    ErrorMessage = "SERVER ERROR: " + responseInfo.ErrorResponse.Message;
                }

            }
            catch (Exception ex)
            {
                ErrorMessage = $"Error retrieving room list: {ex.Message}";
            }
        }

    }
}

