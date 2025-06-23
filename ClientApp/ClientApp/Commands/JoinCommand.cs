using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Stores;
using ClientApp.ViewModels;

namespace ClientApp.Commands
{
    public class JoinCommand : CommandBase
    {
        private INavigationService _navigationService;
        private readonly RequestsExchangeService _requestsExchangeService;
        public JoinCommand(
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService
            )
        {
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService;
        }
        public override bool CanExecute(object parameters)
        {
            if (parameters is not JoinRoomViewModel joinRoomViewModel) 
            {
                return false; 
            }
            return joinRoomViewModel.SelectedRoom != null;
        }

        public override async void Execute(object parameters)
        {
            if (parameters is not JoinRoomViewModel joinRoomViewModel) 
            {
                return; 
            }

            if (joinRoomViewModel.SelectedRoom == null) 
            {
                joinRoomViewModel.ErrorMessage = "Please select a room to join.";
                return;
            }

            try
            {
                var selectedRoomId = joinRoomViewModel.SelectedRoom.RoomData.Id;
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
                        joinRoomViewModel.ErrorMessage = joinResponse.Errors.GeneralError;
                    }
                }
  

            }
            catch (Exception ex)
            {
                joinRoomViewModel.ErrorMessage = $"Failed to join room: {ex.Message}";
            }
        }
    }
}
