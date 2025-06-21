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
    class RoomAdminViewModel : ScreenViewModelBase
    {
        private UserStore userStore;
        private readonly RequestsExchangeService _requestsExchangeService;
        private CancellationTokenSource _checkRoomStateCTS;
        private readonly int refreshMS = 300;
        private LoggedUser _admin;
        private string _errorMessage;

        
        public RoomAdminViewModel(
            RequestsExchangeService requestsExchangeService,
            RoomDataStore roomDataStore,
            UserStore userState,
            StartGameCommand startGameCommand,
            LeaveRoomCommand leaveRoomCommand,
            AmIAdminStore amIAdminStore)
        {
            amIAdminStore.AmIAdmin = true;

            this.userStore = userState;
            this._requestsExchangeService = requestsExchangeService;
            this.StartGameCmd = startGameCommand;
            this.CloseRoomCmd = leaveRoomCommand;
            this.RoomDataStore = roomDataStore;

            Players.CollectionChanged += (s, e) => OnPropertyChanged(nameof(PlayersInfo));
        }

        public string PlayersInfo => $"{this.Players.Count() + 1}/{this.RoomDataStore.CurrentRoomData.MaxPlayers}";

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

        public string ErrorMessage
        {
            get => _errorMessage;
            set
            { 
                _errorMessage = value;
                OnPropertyChanged();
            }
        }

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
            if (!responseInfo.NormalResponse)
                return;
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
