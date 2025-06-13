using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.ViewModels;
using System;
using System.Collections.Generic;

namespace ClientApp.Commands
{
    class LogoutCommand : CommandBase
    {
        private INavigationService _navigationService;
        private readonly RequestsExchangeService _requestsExchangeService;
        MenuViewModel _menuViewModel;

        /// <summary>
        /// Private constructor for the MenuPageViewModel. Initializes the commands for the actions available in the menu.
        /// </summary>
        public LogoutCommand(
            MenuViewModel menuViewModel,
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService)
        {
            this._menuViewModel = menuViewModel;
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService;
        }

        /// <summary>
        /// Logs the user out and navigates to the LoginPage if the logout is successful.
        /// </summary>
        public override async void Execute(object parameter)
        {
            LogoutRequest request = new LogoutRequest();
            ResponseInfo<LogoutResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<LogoutResponse>(request);

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
