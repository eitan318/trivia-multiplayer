using ClientApp.Commands;
using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using System.Collections.ObjectModel;
using System.Windows.Input;
using ClientApp.Views.Screens;
using System.Threading;
using System.Threading.Tasks;
using ClientApp.Stores;


namespace ClientApp.ViewModels
{
    class MemberRoomViewModel : ViewModelBase
    {
        private UserStore _userStore;
        private readonly RequestsExchangeService _requestsExchangeService;
        private readonly INavigationService _navigationService;
        private CancellationTokenSource _checkRoomStateCTS;

        public MemberRoomViewModel(
            INavigationService navigationService,
            RoomDataStore roomDataStore,
            UserStore userStore,
            RequestsExchangeService requestsExchangeService)
        {
            this._navigationService = navigationService;
            this._userStore = userStore;
            this._requestsExchangeService = requestsExchangeService;
            this.LeaveRoomCmd = new LeaveRoomCommand(navigationService, requestsExchangeService, null);
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

        public ObservableCollection<LoggedUser> Players { get; set; } = new ObservableCollection<LoggedUser>();

        public LoggedUser Admin { get; set; }

        public RoomDataStore RoomDataStore { get; set; }

        public ICommand LeaveRoomCmd { get; }

        private async Task PeriodicallyCheckRoomStateLoop(CancellationToken token)
        {
            try
            {
                while (!token.IsCancellationRequested)
                {
                    await PeriodicallyCheckRoomState();
                    await Task.Delay(5000, token); // Pass the token to allow cancellation
                }
            }
            catch (OperationCanceledException)
            {
                // Task was canceled; clean up if necessary
            }
        }

        private async Task PeriodicallyCheckRoomState()
        {
            var getRoomStatusRequest = new GetRoomStateRequest();
            ResponseInfo<GetRoomStateResponse> responseInfo =
                await _requestsExchangeService.ExchangeRequest<GetRoomStateResponse>(getRoomStatusRequest);
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

            if (roomState.RoomStatus == RoomStatus.Closed)
            {
                LeaveRoomCmd.Execute(null);
            }

            if (roomState.RoomStatus == RoomStatus.InGame)
            {
                _navigationService.NavigateTo<GameViewModel>();
            }
        }
    }
}

