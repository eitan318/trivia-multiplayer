using ClientApp.Commands;
using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls.Primitives;
using System.Windows.Input;

namespace ClientApp.ViewModels
{
    class AdminRoomPageViewModel : BaseViewModel
    {
        /// <summary>
        /// Provides a singleton instance of the <see cref="MemberRoomPageViewModel"/>.
        /// </summary>
        public static AdminRoomPageViewModel Instance(RoomData roomData, string user)
        {
            return GetInstance(() => new AdminRoomPageViewModel(roomData, user));
        }

        private AdminRoomPageViewModel(RoomData roomData, string user)
        {
            this.user = user;
            this.RefreshCommand = new RelayCommand(RefreshPlayers);
            this.StartGameCommand = new RelayCommand(StartGame);
            this.CloseRoomCommand = new RelayCommand(CloseRoom);
            this.roomData = roomData;
            RefreshPlayers();
        }

        private RoomData roomData;

        public ICommand RefreshCommand { get; }

        public ICommand StartGameCommand { get; }
        public ICommand CloseRoomCommand { get; }

        /// <summary>
        /// Collection of players currently in the room.
        /// </summary>
        public ObservableCollection<LoggedUser> Players { get; set; } = new ObservableCollection<LoggedUser>();

        public LoggedUser Admin { get; set; }

        private string user;


        /// <summary>
        /// Sends a request to retrieve and populate the player list for the room.
        /// </summary>
        private async void RefreshPlayers()
        {
            var getPlayersRequest = new GetPlayersInRoomRequest(roomData.Id);
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
                Admin.IsMe = Admin.Username == user;
                foreach (var player in response.Players.Skip(1)) // Add remaining players
                {
                    player.IsMe = player.Username ==user;
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
