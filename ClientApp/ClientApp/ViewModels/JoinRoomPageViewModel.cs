using ClientApp.Commands;
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
        JoinCommand = new RelayCommand(async () => await JoinRoom(), CanJoinRoom);
        _ = Refresh(); // Fire and forget
    }

    public static JoinRoomViewModel Instance(Page owner)
    {
        return GetInstance(() => new JoinRoomViewModel(owner));
    }

    private Page ownerPage;
    private List<RoomData> _rooms;
    private string _errorMessage;
    private RoomData? _selectedRoom;

    public List<RoomData> Rooms
    {
        get => _rooms;
        set
        {
            _rooms = value;
            OnPropertyChanged();
        }
    }

    public string ErrorMessage
    {
        get => _errorMessage;
        set
        {
            _errorMessage = value;
            OnPropertyChanged();
        }
    }

    public RoomData? SelectedRoom
    {
        get => _selectedRoom;
        set
        {
            _selectedRoom = value;
            OnPropertyChanged();
            // Notify JoinCommand that its state may have changed
            ((RelayCommand)JoinCommand).RaiseCanExecuteChanged();
        }
    }

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

            // Clear selection after refreshing to ensure consistency
            SelectedRoom = null;
        }
        catch (Exception ex)
        {
            ErrorMessage = $"Error retrieving room list: {ex.Message}";
        }
    }

    private bool CanJoinRoom()
    {
        return SelectedRoom != null;
    }

    public async Task JoinRoom()
    {
        if (SelectedRoom == null)
        {
            ErrorMessage = "Please select a room to join.";
            return;
        }

        try
        {
            var selectedRoomId = SelectedRoom.Value.Id;
            var request = new JoinRoomRequest(selectedRoomId);
            var responseInfo = await RequestsExchangeService.ExchangeRequest(request);

            if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
            {
                var error = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
                ErrorMessage = "SERVER ERROR: " + error.Message;
                return;
            }

            var joinResponse = JsonResponseDeserialize.DeserializeResponse<JoinRoomResponse>(responseInfo);
            if(joinResponse.Status == 0)
            {
                MyNavigationService.Navigate(new RoomPage(SelectedRoom.Value));
            }
            else
            {
                ErrorMessage = joinResponse.Errors.GeneralError;
            }
        }
        catch (Exception ex)
        {
            ErrorMessage = $"Failed to join room: {ex.Message}";
        }
    }
}
