using ClientApp.Commands;
using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using System.Collections.ObjectModel;
using System.Windows.Input;
using ClientApp.Stores;


namespace ClientApp.ViewModels
{
    class RoomMemberViewModel : ScreenViewModelBase
    {
        private UserStore _userStore;
        private readonly RequestsExchangeService _requestsExchangeService;
        private readonly INavigationService _navigationService;
        private CancellationTokenSource _checkRoomStateCTS;
        private LoggedUser _admin;
        private readonly int refreshMS = 300;
        public RoomMemberViewModel(
            INavigationService navigationService,
            RoomDataStore roomDataStore,
            UserStore userStore,
            RequestsExchangeService requestsExchangeService,
            AmIAdminStore amIAdminStore,
            Is1v1GameStore is1v1GameStore,
            LeaveRoomCommand leaveRoomCommand)
        {
            is1v1GameStore.is1v1Game = false;
            amIAdminStore.AmIAdmin = false;

            this._navigationService = navigationService;
            this._userStore = userStore;
            this._requestsExchangeService = requestsExchangeService;
            this.LeaveRoomCmd = leaveRoomCommand;
            this.RoomDataStore = roomDataStore;

            Players.CollectionChanged += (s, e) => OnPropertyChanged(nameof(PlayersInfo));

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

        public string PlayersInfo => $"{this.Players.Count() + 1}/{this.RoomDataStore.CurrentRoomData.MaxPlayers}";

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

        public RoomDataStore RoomDataStore { get; set; }

        public IAsyncCommand LeaveRoomCmd { get; }

        private async Task PeriodicallyCheckRoomStateLoop(CancellationToken token)
        {
            try
            {
                while (!token.IsCancellationRequested)
                {
                    await PeriodicallyCheckRoomState();
                    await Task.Delay(refreshMS, token); // Pass the token to allow cancellation
                }
            }
            catch (OperationCanceledException)
            {
                // Task was canceled; clean up if necessary
            }
        }

        private async Task PeriodicallyCheckRoomState()
        {
            ResponseInfo<GetRoomStateResponse> responseInfo =
                await _requestsExchangeService.ExchangeRequest<GetRoomStateResponse>(RequestsCodes.GetRoomStateRequest);
            
            if (!responseInfo.NormalResponse)
                return;
            GetRoomStateResponse response = (GetRoomStateResponse)responseInfo.Response;
            RoomState roomState = response.RoomState;

            // Update Players on the UI thread
            App.Current.Dispatcher.Invoke(() =>
            {
                Players.Clear();
                if (roomState.Players != null && roomState.Players.Any())
                {
                    Admin = roomState.Players.First();
                    Admin.IsMe = Admin.Username == _userStore.Username;
                    foreach (var player in roomState.Players.Skip(1))
                    {
                        player.IsMe = player.Username == _userStore.Username;
                        Players.Add(player);
                    }
                }
            });

            if (roomState.RoomStatus == RoomStatus.Closing)
            {
                LeaveRoomCmd.ExecuteAsync(null);
            }

            if (roomState.RoomStatus == RoomStatus.StartingGame)
            {
                App.Current.Dispatcher.Invoke(() =>
                {
                     _navigationService.NavigateTo<GameAnsweringViewModel>();
                });

            }
        }
    }
}

