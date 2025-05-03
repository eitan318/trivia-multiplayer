using ClientApp.Commands;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Models;
using ClientApp.Services;
using ClientApp.ViewModels;
using ClientApp.Views.Pages;
using System.Windows.Controls;
using System.Windows.Input;
using Microsoft.Xaml.Behaviors.Media;

public class JoinRoomViewModel : BaseViewModel
{
    private JoinRoomViewModel(Page owner, string user)
    {
        this.ownerPage = owner;
        this.user = user;
        RefreshCommand = new RelayCommand(async () => await Refresh());
        JoinCommand = new RelayCommand(async () => await JoinRoom(), CanJoinRoom);
        _ = Refresh(); // Fire and forget
    }

    public static JoinRoomViewModel Instance(Page owner, string user)
    {
        return GetInstance(() => new JoinRoomViewModel(owner, user));
    }

    private string user;
    private Page ownerPage;
    private List<RoomPreview> _rooms;
    private string _errorMessage;
    private RoomPreview? _selectedRoom;

    public List<RoomPreview> Rooms
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

    public RoomPreview? SelectedRoom
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
            var selectedRoomId = SelectedRoom.Value.RoomData.Id;
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
                MyNavigationService.Navigate(new MemberRoomPage(SelectedRoom.Value.RoomData, user));
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
