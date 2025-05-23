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
    class AdminRoomViewModel : ViewModelBase
    {
        private UserStore userState;
        private readonly RequestsExchangeService _requestsExchangeService;

        public AdminRoomViewModel(
            RequestsExchangeService requestsExchangeService, 
            RoomDataStore roomDataStore, 
            UserStore userState)
        {
            this.userState = userState;
            this._requestsExchangeService = requestsExchangeService;
            this.RefreshCmd = new RelayCommand(RefreshPlayers);
            this.StartGameCmd = new RelayCommand(StartGame);
            this.CloseRoomCmd = new RelayCommand(CloseRoom);
            this.RoomDataStore = roomDataStore;
            RefreshPlayers();
        }

        public RoomDataStore RoomDataStore { get; set; }
        

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
            var getPlayersRequest = new GetPlayersInRoomRequest(RoomDataStore.CurrentRoomData.Id);
            ResponseInfo responseInfo = await this._requestsExchangeService.ExchangeRequest(getPlayersRequest);

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
