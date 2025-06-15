using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Stores;
using ClientApp.ViewModels;

namespace ClientApp.Commands
{
    class JoinCommand : CommandBase
    {
        private INavigationService _navigationService;
        private readonly RequestsExchangeService _requestsExchangeService;
        private JoinRoomViewModel _joinRoomViewModel;
        public JoinCommand(
            JoinRoomViewModel joinRoomViewModel,
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService,
            RoomDataStore roomDataStore
            )
        {
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService;
            this._joinRoomViewModel = joinRoomViewModel;
        }
        public override bool CanExecute(object parameters)
        {
            return _joinRoomViewModel.SelectedRoom != null;
        }

        public override async void Execute(object parameters)
        {
            if (_joinRoomViewModel.SelectedRoom == null) 
            {
                _joinRoomViewModel.ErrorMessage = "Please select a room to join.";
                return;
            }

            try
            {
                var selectedRoomId = _joinRoomViewModel.SelectedRoom.RoomData.Id;
                var request = new JoinRoomRequest(selectedRoomId);
                ResponseInfo<JoinRoomResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<JoinRoomResponse>(request);

                if (responseInfo.NormalResponse)
                {
                    var joinResponse = responseInfo.Response;
                    if(joinResponse.Status == 0)
                    {
                        _navigationService.NavigateTo<RoomMemberViewModel>();
                    }
                    else
                    {
                        _joinRoomViewModel.ErrorMessage = joinResponse.Errors.GeneralError;
                    }
                }
  

            }
            catch (Exception ex)
            {
                _joinRoomViewModel.ErrorMessage = $"Failed to join room: {ex.Message}";
            }
        }
    }
}
