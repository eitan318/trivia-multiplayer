using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.ViewModels;
using ClientApp.Stores;
using ClientApp.Models.Requests;

namespace ClientApp.Commands
{
    class LeaveWaitingListCommand : CommandBase, IAsyncCommand
    {
        private INavigationService _navigationService;
        private readonly RequestsExchangeService _requestsExchangeService;
        public LeaveWaitingListCommand(
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService
            )
        {
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService;
        }

        public override async Task ExecuteAsync(object parameters)
        {
            if (parameters is not Waiting1v1ViewModel waiting1v1ViewModel) 
            {
                return; 
            }
            ResponseInfo<Leave1v1WaitingListResponse> responseInfo = await _requestsExchangeService.ExchangeRequest
                <Leave1v1WaitingListResponse>(RequestsCodes.Leave1v1WaitingListRequest);

            if (!responseInfo.NormalResponse)
            {
                return;
            }
            if(responseInfo.Response.Status != 0)
            {
                waiting1v1ViewModel.ErrorMessage = responseInfo.Response.Errors.GeneralError;
                return;
            }

            _navigationService.NavigateTo<MenuViewModel>();

        }
    }
}
