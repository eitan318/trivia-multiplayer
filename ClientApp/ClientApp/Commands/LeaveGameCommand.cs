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
    class LeaveGameCommand : CommandBase
    {
        private readonly INavigationService _navigationService;
        private readonly RequestsExchangeService _requestsExchangeService;
        public LeaveGameCommand(INavigationService navigationService,
            RequestsExchangeService requestsExchangeService) 
        {
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService;
        }


        public override async void Execute(object parameter)
        {
            LeaveGameRequest request = new LeaveGameRequest();
            ResponseInfo<LeaveGameResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<LeaveGameResponse>(request);

            if (responseInfo.NormalResponse)
            {
                LeaveGameResponse leaveGameResponse = responseInfo.Response;

                if(leaveGameResponse.Status == 0)
                {
                    this._navigationService.GoBack();
                }
                else
                {

                } 
            }
        }
    }
}
