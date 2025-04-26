using ClientApp.Commands;
using ClientApp.Enums;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Models;
using ClientApp.Services;
using ClientApp.ViewModels;
using ClientApp.Views.Pages;
using System.Windows.Controls;
using System.Windows.Input;

public class JoinRoomViewModel : BaseViewModel
{
    private JoinRoomViewModel(Page owner)
    {
        this.ownerPage = owner;
        RefreshCommand = new RelayCommand(async () => await Refresh());
        JoinCommand = new RelayCommand(async () => await JoinRoom());
        _ = Refresh(); // Fire and forget
    }

    public static JoinRoomViewModel Instance(Page owner)
    {
        return GetInstance(() => new JoinRoomViewModel(owner));
    }

    private Page ownerPage;
    private List<RoomData> _rooms;
    private string _errorMessage;
    private uint? _selectedRoomId;

    public List<RoomData> Rooms { get => _rooms; set { _rooms = value; OnPropertyChanged(); } }
    public string ErrorMessage { get => _errorMessage; set { _errorMessage = value; OnPropertyChanged(); } }
    public uint? SelectedRoomId { get => _selectedRoomId; set { _selectedRoomId = value; OnPropertyChanged(); } }

    public ICommand RefreshCommand { get; }
    public ICommand JoinCommand { get; }

    public async Task Refresh()
    {
        try
        {
            var request = new GetRoomsRequest();
            var responseInfo = await RequestsExchangeService.ExchangeRequest(request);

            if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
            {
                var error = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
                ErrorMessage = "SERVER ERROR: " + error.Message;
                return;
            }

            var roomResponse = JsonResponseDeserialize.DeserializeResponse<GetRoomsResponse>(responseInfo);
            Rooms = roomResponse.Rooms;
        }
        catch (Exception ex)
        {
            ErrorMessage = $"Error retrieving room list: {ex.Message}";
        }
    }

    public async Task JoinRoom()
    {
        if (SelectedRoomId == null)
        {
            ErrorMessage = "Please select a room to join.";
            return;
        }

        var selectedRoom = Rooms?.FirstOrDefault(r => r.Id == SelectedRoomId);
        if (selectedRoom == null)
        {
            ErrorMessage = "Selected room no longer exists.";
            return;
        }

        try
        {
            var selectedRoomId = selectedRoom.Value.Id;
            var request = new JoinRoomRequest(selectedRoomId);
            var responseInfo = await RequestsExchangeService.ExchangeRequest(request);

            if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
            {
                var error = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
                ErrorMessage = "SERVER ERROR: " + error.Message;
                return;
            }

            var joinResponse = JsonResponseDeserialize.DeserializeResponse<JoinRoomResponse>(responseInfo);
            switch (joinResponse.Status)
            {
                case (byte)JoinRoomRequestStatus.Success:
                    MyNavigationService.Navigate(new RoomPage(selectedRoomId));
                    break;
                case (byte)JoinRoomRequestStatus.UnknownRoom:
                    ErrorMessage = "Room doesn't exist.";
                    break;
            }
        }
        catch (Exception ex)
        {
            ErrorMessage = $"Failed to join room: {ex.Message}";
        }
    }
}
