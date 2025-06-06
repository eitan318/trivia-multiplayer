using ClientApp.Commands;
using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Stores;
using System.Collections.ObjectModel;
using System.Windows.Input;

namespace ClientApp.ViewModels
{
    class RoomAdminViewModel : ViewModelBase
    {
        private UserStore userStore;
        private readonly RequestsExchangeService _requestsExchangeService;
        private CancellationTokenSource _checkRoomStateCTS;
        private readonly int refreshMS = 300;
        private LoggedUser _admin;

        public RoomAdminViewModel(
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService,
            RoomDataStore roomDataStore,
            UserStore userState)
        {

            this.userStore = userState;
            this._requestsExchangeService = requestsExchangeService;
            this.StartGameCmd = new StartGameCommand(navigationService, requestsExchangeService, this);
            this.CloseRoomCmd = new CloseRoomCommand(navigationService, requestsExchangeService, this);
            this.RoomDataStore = roomDataStore;
        }

        public override void OnNavigatedTo()
        {
            this._checkRoomStateCTS = new CancellationTokenSource();
            Task.Run(() => PeriodicallyCheckRoomStateLoop(_checkRoomStateCTS.Token));
        }

        public override void OnNavigatedAway()
        {
            _checkRoomStateCTS.Cancel();
            _checkRoomStateCTS.Dispose();
        }


        public RoomDataStore RoomDataStore { get; set; }

        // Commands
        public ICommand StartGameCmd { get; }
        public ICommand CloseRoomCmd { get; }

        public ObservableCollection<LoggedUser> Players { get; set; } = new ObservableCollection<LoggedUser>();

        public LoggedUser Admin
        {
            get => _admin;
            set
            {
                if (_admin != value)
                {
                    _admin = value;
                    OnPropertyChanged(nameof(Admin));
                }
            }
        }

        public string ErrorMessage { get; set; }

        private async Task PeriodicallyCheckRoomStateLoop(CancellationToken token)
        {
            try
            {
                while (!token.IsCancellationRequested)
                {
                    await PeriodicallyCheckRoomState();
                    await Task.Delay(refreshMS, token);
                }
            }
            catch (OperationCanceledException)
            {
                // Handle cancellation (optional)
            }
        }

        private async Task PeriodicallyCheckRoomState()
        {
            var getRoomStatusRequest = new GetRoomStateRequest();
            ResponseInfo<GetRoomStateResponse> responseInfo =
                await _requestsExchangeService.ExchangeRequest<GetRoomStateResponse>(getRoomStatusRequest);
            GetRoomStateResponse response = responseInfo.Response;
            RoomState roomState = response.RoomState;

            // Update Players on the UI thread
            App.Current.Dispatcher.Invoke(() =>
            {
                this.Players.Clear();
                if (roomState.Players != null && roomState.Players.Any())
                {
                    Admin = roomState.Players.First(); // Set Admin
                    Admin.IsMe = Admin.Username == userStore.Username;
                    foreach (var player in roomState.Players.Skip(1)) // Add remaining players
                    {
                        player.IsMe = player.Username == userStore.Username;
                        Players.Add(player);
                    }
                }
            });
        }
    }

}
