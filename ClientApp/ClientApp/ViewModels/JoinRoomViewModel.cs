using ClientApp.Commands;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Models;
using ClientApp.Services;
using ClientApp.ViewModels;
using System.Windows.Input;
using ClientApp.Stores;

namespace ClientApp.ViewModels
{

public class JoinRoomViewModel : ViewModelBase
{
    private INavigationService _navigationService;
    private RoomDataStore _roomDataStore;
    public JoinRoomViewModel(INavigationService navigationService, RoomDataStore roomDataStore)
    {
        this._navigationService = navigationService;
            this._roomDataStore = roomDataStore;
        RefreshCmd = new RelayCommand(async () => await Refresh());
        JoinCmd = new RelayCommand(async () => await JoinRoom(), CanJoinRoom);
        _ = Refresh(); // Fire and forget
    }


    // Fields
    private List<RoomPreview> _rooms;
    private RoomPreview? _selectedRoom;
    
    // Error message fields
    private string _errorMessage;


    //Properties
    public List<RoomPreview> Rooms
    {
        get => _rooms;
        set
        {
            _rooms = value;
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
            ((RelayCommand)JoinCmd).RaiseCanExecuteChanged();
        }
    }

    
    // Errore message properties
    public string ErrorMessage
    {
        get => _errorMessage;
        set
        {
            _errorMessage = value;
            OnPropertyChanged();
        }
    }


    // Commands
    public ICommand RefreshCmd { get; }
    public ICommand JoinCmd { get; }


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
                this._roomDataStore.CurrentRoom = _selectedRoom.Value.RoomData;
                _navigationService.NavigateTo<MemberRoomViewModel>();
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
}

