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

        public StartGameCommand(INavigationService navigationService, 
            RequestsExchangeService requestsExchangeService 
            )
        {
            _navigationService = navigationService;
            _requestsExchangeService = requestsExchangeService;

        }

        public override async void Execute(object parameter)
        {
            if(parameter is not RoomAdminViewModel roomAdminViewModel)
            {
                return;
            }
            try
            {
                var request = new StartGameRequest();
                ResponseInfo<StartGameResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<StartGameResponse>(request);

                if (responseInfo.NormalResponse)
                {
                    var startGameResponse = responseInfo.Response;
                    if(startGameResponse.Status == 0)
                    {
                        _navigationService.NavigateTo<GameAnsweringViewModel>(); 
                    }
                    else
                    {
                        roomAdminViewModel.ErrorMessage = startGameResponse.Errors.GeneralError;
                    }
                }

            }
            catch (Exception ex)
            {
                roomAdminViewModel.ErrorMessage = $"Failed to start game in room: {ex.Message}";
            }
        }
        
    }
}
