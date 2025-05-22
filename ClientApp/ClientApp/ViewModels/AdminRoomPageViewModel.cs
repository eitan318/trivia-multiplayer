using ClientApp.Commands;
using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Views.States;
using System.Collections.ObjectModel;
using System.Windows.Input;

namespace ClientApp.ViewModels
{
    class AdminRoomPageViewModel : ViewModelBase
    {
        private UserState userState;

        /// <summary>
        /// Provides a singleton instance of the <see cref="MemberRoomViewModel"/>.
        /// </summary>
        public static AdminRoomPageViewModel Instance(RoomData roomData, UserState userState)
        {
            return GetInstance(() => new AdminRoomPageViewModel(roomData, userState));
        }

        private AdminRoomPageViewModel(RoomData roomData, UserState userState)
        {
            this.userState = userState;
            this.RefreshCmd = new RelayCommand(RefreshPlayers);
            this.StartGameCmd = new RelayCommand(StartGame);
            this.CloseRoomCmd = new RelayCommand(CloseRoom);
            this.RoomData = roomData;
            RefreshPlayers();
        }

        public RoomData RoomData { get; set; }
        

        // Commands

        public ICommand RefreshCmd { get; }
        public ICommand StartGameCmd { get; }
        public ICommand CloseRoomCmd { get; }

        /// <summary>
        /// Collection of players currently in the room.
        /// </summary>
        public ObservableCollection<LoggedUser> Players { get; set; } = new ObservableCollection<LoggedUser>();

        public LoggedUser Admin { get; set; }




        /// <summary>
        /// Sends a request to retrieve and populate the player list for the room.
        /// </summary>
        private async void RefreshPlayers()
        {
            var getPlayersRequest = new GetPlayersInRoomRequest(RoomData.Id);
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
                Admin.IsMe = Admin.Username == userState.Username;
                foreach (var player in response.Players.Skip(1)) // Add remaining players
                {
                    player.IsMe = player.Username == userState.Username;
                    Players.Add(player);
                }
            }
        }

        private void StartGame()
        {

        }


        private void CloseRoom()
        {

        }

    }
}
