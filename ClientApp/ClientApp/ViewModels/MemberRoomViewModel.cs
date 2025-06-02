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
        private CancellationTokenSource _cts;

        public MemberRoomViewModel(
            INavigationService navigationService,
            RoomDataStore roomDataStore, 
            UserStore userStore,
            RequestsExchangeService requestsExchangeService) 
        {
            this._userStore = userStore;
            this._requestsExchangeService = requestsExchangeService;
            this.RefreshCmd = new RelayCommand(RefreshPlayers);
            this.LeaveRoomCmd = new LeaveRoomCommand(this,navigationService,requestsExchangeService,null);
            this.RoomDataStore = roomDataStore;
            RefreshPlayers();

            this._cts = new CancellationTokenSource();
            Task.Run(() => PeriodicallyCheckRoomStateLoop(_cts.Token));
        }

        /// <summary>
        /// Collection of players currently in the room.
        /// </summary>
        public ObservableCollection<LoggedUser> Players { get; set; } = new ObservableCollection<LoggedUser>();

        public LoggedUser Admin { get; set; }

        public RoomDataStore RoomDataStore { get; set; }


        //Commands
        public ICommand RefreshCmd { get; }
        public ICommand LeaveRoomCmd { get; }


        /// <summary>
        /// runs as a thread in the background, runs with a while loop and calls PeriodicallyCheckRoomState to check on room,
        /// stops if cancellation token is canceled.
        /// </summary>
        /// <param name="token"></param>
        /// <returns></returns>
        private async Task PeriodicallyCheckRoomStateLoop(CancellationToken token)
        {
            while (!token.IsCancellationRequested)
            {
                await PeriodicallyCheckRoomState();
                await Task.Delay(300, token); // 0.3 seconds
            }
        }

        /// <summary>
        /// Periodically checks the room state, if room is closed than calling the leave room command.
        /// </summary>
        /// <returns></returns>
        private async Task PeriodicallyCheckRoomState()
        {
            //Check get room status from server.
            var getRoomStatusRequest = new GetRoomStateRequest();
            ResponseInfo<GetRoomStateResponse> responseInfo =
                await _requestsExchangeService.ExchangeRequest<GetRoomStateResponse>(getRoomStatusRequest);
            GetRoomStateResponse response = (GetRoomStateResponse)responseInfo.Response;

            if (response.RoomState.RoomStatus == RoomStatus.Closed) //if status of room is closed
            {
                LeaveRoomCmd.Execute(null);
                _cts.Cancel();
            }
        }


        /// <summary>
        /// Sends a request to retrieve and populate the player list for the room.
        /// </summary>
        private async void RefreshPlayers()
        {
            var getPlayersRequest = new GetPlayersInRoomRequest(RoomDataStore.CurrentRoomData.Id);
            ResponseInfo<GetPlayersInRoomResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<GetPlayersInRoomResponse>(getPlayersRequest);

            if (responseInfo.NormalResponse)
            {
                GetPlayersInRoomResponse response = (GetPlayersInRoomResponse)responseInfo.Response;
                Players.Clear();
                if (response.Players != null && response.Players.Any())
                {
                    Admin = response.Players.First(); // Set Admin
                    Admin.IsMe = Admin.Username == this._userStore.Username;
                    foreach (var player in response.Players.Skip(1)) 
                    {
                        player.IsMe = player.Username == this._userStore.Username;
                        Players.Add(player);
                    }
                }
            }
            else
            {
                // Handle error appropriately.
                return;
            }

        }

    }
}
