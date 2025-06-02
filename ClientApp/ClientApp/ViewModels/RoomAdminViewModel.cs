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

        public RoomAdminViewModel(
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService, 
            RoomDataStore roomDataStore, 
            UserStore userState)
        {
            this.userStore = userState;
            this._requestsExchangeService = requestsExchangeService;
            this.StartGameCmd = new StartGameCommand(navigationService, requestsExchangeService, this);
            this.CloseRoomCmd = new RelayCommand(CloseRoom);
            this.RoomDataStore = roomDataStore;

            Task.Run(() => PeriodicallyCheckRoomStateLoop());
        }

        public RoomDataStore RoomDataStore { get; set; }
        

        // Commands
        public ICommand StartGameCmd { get; }
        public ICommand CloseRoomCmd { get; }

        /// <summary>
        /// Collection of players currently in the room.
        /// </summary>
        public ObservableCollection<LoggedUser> Players { get; set; } = new ObservableCollection<LoggedUser>();

        public LoggedUser Admin { get; set; }

        public string ErrorMessage { get; set; }


        /// <summary>
        /// runs as a thread in the background, runs with a while loop and calls PeriodicallyCheckRoomState to check on room,
        /// stops if cancellation token is canceled.
        /// </summary>
        /// <param name="token"></param>
        /// <returns></returns>
        private async Task PeriodicallyCheckRoomStateLoop()
        {
            while (true)
            {
                await PeriodicallyCheckRoomState();
                await Task.Delay(5000); // 0.3 seconds
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
            RoomState roomState = response.RoomState;

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
        }


        private void CloseRoom()
        {

        }

    }
}
