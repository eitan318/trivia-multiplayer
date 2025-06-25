using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.ViewModels;
using System;
using System.Collections.Generic;

namespace ClientApp.Commands
{
    public class LogoutCommand : CommandBase, IAsyncCommand
    {
        private INavigationService _navigationService;
        private readonly RequestsExchangeService _requestsExchangeService;

        /// <summary>
        /// Private constructor for the MenuPageViewModel. Initializes the commands for the actions available in the menu.
        /// </summary>
        public LogoutCommand(
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService)
        {
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService;
        }

        /// <summary>
        /// Logs the user out and navigates to the LoginPage if the logout is successful.
        /// </summary>
        public override async Task ExecuteAsync(object parameter)
        {
            ResponseInfo<LogoutResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<LogoutResponse>(RequestsCodes.LogoutRequest);

            if (responseInfo.NormalResponse)
            {
                LogoutResponse logoutResponse = responseInfo.Response;

                if(logoutResponse.Status == 0)
                {
                    this._navigationService.NavigateTo<LoginViewModel>();
                }
                else
                {

                } 
            }
        }
    }
}
