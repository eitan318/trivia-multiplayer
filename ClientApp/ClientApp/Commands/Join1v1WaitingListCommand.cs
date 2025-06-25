using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Commands
{
    class Join1v1WaitingListCommand : CommandBase, IAsyncCommand
    {
        private INavigationService _navigationService;
        private readonly RequestsExchangeService _requestsExchangeService;
        public Join1v1WaitingListCommand(
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService
            )
        {
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService;
        }

        public override async Task ExecuteAsync(object parameters)
        {
            if (parameters is not MenuViewModel menuViewModel) 
            {
                return; 
            }
            ResponseInfo<Join1v1WaitingListResponse> responseInfo = await _requestsExchangeService.ExchangeRequest
                <Join1v1WaitingListResponse>(RequestsCodes.Join1v1WaitingListRequest);

            if (!responseInfo.NormalResponse)
            {
                return;
            }
            if(responseInfo.Response.Status != 0)
            {
                menuViewModel.ErrorMessage = responseInfo.Response.Errors.GeneralError;
                return;
            }

            _navigationService.NavigateTo<Waiting1v1ViewModel>();

        }
    }
}
