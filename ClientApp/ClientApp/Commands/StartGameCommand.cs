using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.ViewModels;

namespace ClientApp.Commands
{
    class StartGameCommand : CommandBase
    {
        private INavigationService _navigationService;
        private readonly RequestsExchangeService _requestsExchangeService;
        RoomAdminViewModel _roomAdminViewModel;

        public StartGameCommand(INavigationService navigationService, 
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
                var request = new StartGameRequest();
                ResponseInfo<StartGameResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<StartGameResponse>(request);

                if (responseInfo.NormalResponse)
                {
                    var startGameResponse = responseInfo.Response;
                    if(startGameResponse.Status == 0)
                    {
                        _navigationService.NavigateTo<GameViewModel>(); //Will be game in next version
                    }
                    else
                    {
                        _roomAdminViewModel.ErrorMessage = startGameResponse.Errors.GeneralError;
                    }
                }
                else
                {
                    _roomAdminViewModel.ErrorMessage = "SERVER ERROR: " + responseInfo.ErrorResponse.Message;
                }
  

            }
            catch (Exception ex)
            {
                _roomAdminViewModel.ErrorMessage = $"Failed to start game in room: {ex.Message}";
            }
        }
        
    }
}
