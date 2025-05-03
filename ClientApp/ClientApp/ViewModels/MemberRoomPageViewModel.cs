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
using ClientApp.Views.Pages;
using System.Windows.Controls;
using System.Numerics;

namespace ClientApp.ViewModels
{
    class MemberRoomPageViewModel : BaseViewModel
    {
        /// <summary>
        /// Provides a singleton instance of the <see cref="MemberRoomPageViewModel"/>.
        /// </summary>
        public static MemberRoomPageViewModel Instance(RoomData roomData, string userUsername)
        {
            return GetInstance(() => new MemberRoomPageViewModel(roomData, userUsername));
        }

        private MemberRoomPageViewModel(RoomData roomData, string userUsername) 
        {
            this.RefreshCommand = new RelayCommand(RefreshPlayers);
            this.LeaveRoomCommand = new RelayCommand(LeaveRoom);
            this.RoomData = roomData;
            this.user = userUsername;
            RefreshPlayers();
        }


        public ICommand RefreshCommand { get; }
        public ICommand LeaveRoomCommand { get; }

        /// <summary>
        /// Collection of players currently in the room.
        /// </summary>
        public ObservableCollection<LoggedUser> Players { get; set; } = new ObservableCollection<LoggedUser>();

        public LoggedUser Admin { get; set; }

        public RoomData RoomData { get; set; }


        private string user;


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
                Admin.IsMe = Admin.Username == user;
                foreach (var player in response.Players.Skip(1)) // Add remaining players
                {
                    player.IsMe = player.Username == user;
                    Players.Add(player);
                }
            }
        }


        /// <summary>
        /// Sends a request to retrieve and populate the player list for the room.
        /// </summary>
        void LeaveRoom()
        {
            MyNavigationService.Navigate(new JoinRoomPage(new MenuPage(user), user));
        }

    }
}
