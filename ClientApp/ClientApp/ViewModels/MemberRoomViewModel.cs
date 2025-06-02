using ClientApp.Commands;
using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using System.Collections.ObjectModel;
using System.Windows.Input;
using ClientApp.Views.Screens;
using ClientApp.Stores;

namespace ClientApp.ViewModels
{
    class MemberRoomViewModel : ViewModelBase
    {
        private UserStore _userStore;
        private readonly RequestsExchangeService _requestsExchangeService;

        public MemberRoomViewModel(
            INavigationService navigationService,
            RoomDataStore roomDataStore, 
            UserStore userStore,
            RequestsExchangeService requestsExchangeService) 
        {
            this._userStore = userStore;
            this._requestsExchangeService = requestsExchangeService;
            this.RefreshCmd = new RelayCommand(RefreshPlayers);
            this.LeaveRoomCmd = new NavigateCommand<JoinRoomViewModel>(navigationService);
            this.RoomDataStore = roomDataStore;
            RefreshPlayers();
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




        private async void PeriodiclyCheckRoomState()
        {

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
