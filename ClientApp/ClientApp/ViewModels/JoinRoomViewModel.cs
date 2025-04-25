using ClientApp.Commands;
using ClientApp.Enums;
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
            Refresh();
        }

        public static JoinRoomViewModel Instance(Page owner)
        {
            return GetInstance(() => new JoinRoomViewModel(owner));
        }

        private Page ownerPage;

        private List<RoomData> _rooms;
        private string _errorMessage;
        private int? _selectedRoomId;


        public List<RoomData> Rooms { get => _rooms; set { _rooms = value; OnPropertyChanged(); } }
        public string ErrorMessage { get => _errorMessage; set { _errorMessage = value; OnPropertyChanged(); } }


        public ICommand RefreshCommand { get; }
        public ICommand JoinCommand { get; }


        public async Task Refresh()
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
                Rooms = roomResponse.Rooms;
            }
            catch (Exception ex)
            {
                ErrorMessage = $"Error retrieving room list: {ex.Message}";
            }
        }


        public async Task JoinRoom()
        {
            if (_selectedRoomId == null)
            {
                ErrorMessage = "Please select a room to join.";
                return;
            }

            var selected = Rooms?.FirstOrDefault(r => r.Id == _selectedRoomId);
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
                    JoinRoomResponse joinResponse = JsonResponseDeserialize.DeserializeResponse<JoinRoomResponse>(responseInfo);
                    switch (joinResponse.Status)
                    {
                        case (byte)JoinRoomRequestStatus.Success:
                            // TODO: Navigate to room page
                            break;
                        case (byte)JoinRoomRequestStatus.UnknownRoom:
                            ErrorMessage = "Room doesn't exist";
                            break;
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
