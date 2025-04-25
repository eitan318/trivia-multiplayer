using ClientApp.Commands;
using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Views;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Input;

namespace ClientApp.ViewModels
{
    public class JoinRoomViewModel : BaseViewModel
    {
        private JoinRoomViewModel(Page owner)
        {
            this.ownerPage = owner;
            RefreshCommand = new RelayCommand(async () => await Refresh());
            JoinCommand = new RelayCommand(async () => await JoinRoom());
        }

        public static JoinRoomViewModel Instance(Page owner)
        {
            return GetInstance(() => new JoinRoomViewModel(owner));
        }

        private Page ownerPage;

        private List<RoomData> _rooms;
        private List<string> _roomNames;
        private string _selectedRoom;
        private string _errorMessage;

        public List<string> RoomNames
        {
            get => _roomNames;
            set => SetProperty(ref _roomNames, value);
        }

        public string SelectedRoom
        {
            get => _selectedRoom;
            set => SetProperty(ref _selectedRoom, value);
        }

        public string ErrorMessage
        {
            get => _errorMessage;
            set => SetProperty(ref _errorMessage, value);
        }

        public ICommand RefreshCommand { get; }
        public ICommand JoinCommand { get; }

        /// <summary>
        /// Updates the list of available rooms from the server.
        /// </summary>
        public async Task UpdateList()
        {
            try
            {
                var request = new GetRoomsRequest();
                ResponseInfo responseInfo = await RequestsExchangeService.ExchangeRequest(request);

                if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
                {
                    var error = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
                    ErrorMessage = "SERVER ERROR: " + error.Message;
                    return;
                }

                var roomResponse = JsonResponseDeserialize.DeserializeResponse<GetRoomResponse>(responseInfo);
                _rooms = roomResponse.Rooms;
                RoomNames = _rooms.Select(r => r.name).ToList();
            }
            catch (Exception ex)
            {
                ErrorMessage = $"Error retrieving room list: {ex.Message}";
            }
        }

        public async Task Refresh()
        {
            await UpdateList();
        }

        public async Task JoinRoom()
        {
            if (string.IsNullOrEmpty(SelectedRoom))
            {
                ErrorMessage = "Please select a room to join.";
                return;
            }

            var selected = _rooms?.FirstOrDefault(r => r.name == SelectedRoom);
            if (selected == null)
            {
                ErrorMessage = "Selected room no longer exists.";
                return;
            }

            try
            {
                var request = new JoinRoomRequest(selected.Value.Id);
                ResponseInfo responseInfo = await RequestsExchangeService.ExchangeRequest(request);

                if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
                {
                    var error = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
                    ErrorMessage = "SERVER ERROR: " + error.Message;
                }
                else
                {
                    var joinResponse = JsonResponseDeserialize.DeserializeResponse<NoDataResponse>(responseInfo);
                    string[] errMsg =
                    {
                        "",
                        "Room doesn't exist",
                    };

                    ErrorMessage = errMsg.ElementAtOrDefault(joinResponse.Status) ?? "Unknown error";

                    if (joinResponse.Status == 0)
                    {
                        // TODO: Navigate to room page
                    }
                }
            }
            catch (Exception ex)
            {
                ErrorMessage = $"Failed to join room: {ex.Message}";
            }
        }
    }
}
