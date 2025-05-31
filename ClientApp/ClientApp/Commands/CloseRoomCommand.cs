using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.ViewModels;

namespace ClientApp.Commands
{
    class CloseRoomCommand : CommandBase
    {
        private INavigationService _navigationService;
        private readonly RequestsExchangeService _requestsExchangeService;
        RoomAdminViewModel _roomAdminViewModel;

        public CloseRoomCommand(INavigationService navigationService, 
            RequestsExchangeService requestsExchangeService, 
            RoomAdminViewModel roomAdminViewModel)
        {
            _navigationService = navigationService;
            _requestsExchangeService = requestsExchangeService;
            _roomAdminViewModel = roomAdminViewModel;
        }

        public override async void Execute(object parameter)
        {
            try
            {
                var request = new CloseRoomRequest();
                ResponseInfo<CloseRoomResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<CloseRoomResponse>(request);

                if (responseInfo.NormalResponse)
                {
                    var closeRoomResponse = responseInfo.Response;
                    if(closeRoomResponse.Status == 0)
                    {
                        _navigationService.NavigateTo<MenuViewModel>();
                    }
                    else
                    {
                        _roomAdminViewModel.ErrorMessage = closeRoomResponse.Errors.GeneralError;
                    }
                }
                else
                {
                    _roomAdminViewModel.ErrorMessage = "SERVER ERROR: " + responseInfo.ErrorResponse.Message;
                }
  

            }
            catch (Exception ex)
            {
                _roomAdminViewModel.ErrorMessage = $"Failed to close room: {ex.Message}";
            }
        }
        
    }
}
