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
using System.Windows.Input;

namespace ClientApp.ViewModels
{
    class RoomPageViewModel : BaseViewModel
    {
        /// <summary>
        /// Provides a singleton instance of the <see cref="RoomPageViewModel"/>.
        /// </summary>
        public static RoomPageViewModel Instance(RoomData roomData)
        {
            return GetInstance(() => new RoomPageViewModel(roomData));
        }

        private RoomPageViewModel(RoomData roomData) 
        {
            this.RefreshCommand = new RelayCommand(RefreshPlayers);
            this.roomData = roomData;
            RefreshPlayers();
        }

        private RoomData roomData;

        public ICommand RefreshCommand { get; }

        /// <summary>
        /// Collection of players currently in the room.
        /// </summary>
        public ObservableCollection<Player> Players { get; set; } = new ObservableCollection<Player>();


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
            var playerNames = response.Players;
            Players.Clear();
            foreach (var playerName in playerNames)
            {
                Players.Add(new Player { Username = playerName });
            }
        }

    }
}
