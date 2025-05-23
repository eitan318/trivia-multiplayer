using ClientApp.Commands;
using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using System.Collections.ObjectModel;
using System.Windows.Input;
using ClientApp.Views.Pages;
using ClientApp.Stores;

namespace ClientApp.ViewModels
{
    class MemberRoomViewModel : ViewModelBase
    {
        private UserStore _userState;


        public MemberRoomViewModel(INavigationService navigationService, RoomDataStore roomDataStore, UserStore userState) 
        {
            this._userState = userState;
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




        /// <summary>
        /// Sends a request to retrieve and populate the player list for the room.
        /// </summary>
        private async void RefreshPlayers()
        {
            var getPlayersRequest = new GetPlayersInRoomRequest(RoomDataStore.CurrentRoom.Id);
            ResponseInfo responseInfo = await RequestsExchangeService.ExchangeRequest(getPlayersRequest);

            if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
            {
                // Handle error appropriately.
                return;
            }

            var response = JsonResponseDeserialize.DeserializeResponse<GetPlayersInRoomResponse>(responseInfo);
            Players.Clear();
            if (response.Players != null && response.Players.Any())
            {
                Admin = response.Players.First(); // Set Admin
                Admin.IsMe = Admin.Username == this._userState.Username;
                foreach (var player in response.Players.Skip(1)) 
                {
                    player.IsMe = player.Username == this._userState.Username;
                    Players.Add(player);
                }
            }
        }

    }
}
