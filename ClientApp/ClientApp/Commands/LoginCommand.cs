using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Stores;
using ClientApp.ViewModels;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Navigation;

namespace ClientApp.Commands
{
    class LoginCommand : CommandBase
    {
        private readonly INavigationService _navigationService;
        private UserStore _userStore;
        private readonly RequestsExchangeService _requestsExchangeService;
        private LoginViewModel _loginViewModel;
        
        public LoginCommand( LoginViewModel loginViewModel,
            INavigationService navigationService,
            UserStore userStore,
            RequestsExchangeService requestsExchangeService)
        {
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService;
            this._userStore = userStore;
            this._loginViewModel = loginViewModel;
        }


        public override bool CanExecute(object parameter)
        {
            return !string.IsNullOrWhiteSpace(_loginViewModel.Username) &&
                !string.IsNullOrWhiteSpace(_loginViewModel.Password);
        }

        /// <summary>
        /// Attempts to log in the user by validating the username and password.
        /// If successful, navigates to the menu page. If there is an error, shows the error messages.
        /// </summary>
        public override async void Execute(object parameter)
        {
            _loginViewModel.ErrorMessage = "";
            _loginViewModel.UsernameErrorMessage = "";
            _loginViewModel.PasswordErrorMessage = "";

            try
            {
                // Trim input values
                string trimmedUsername = _loginViewModel.Username?.Trim();
                string trimmedPassword = _loginViewModel.Password?.Trim();

                this._userStore.Username = _loginViewModel.Username;

                // Prepare the login request and send it
                LoginRequest loginRequest = new LoginRequest(trimmedUsername, trimmedPassword);
                ResponseInfo<LoginResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<LoginResponse>(loginRequest);

                // Handle server error response
                if (responseInfo.NormalResponse)
                {
                    LoginResponse loginResponse = responseInfo.Response;
                    if(loginResponse.Status == 0)
                    {
                        this._navigationService.NavigateTo<MenuViewModel>();
                    }
                    else
                    {
                        _loginViewModel.UsernameErrorMessage = loginResponse.Errors.UsernameError;
                        _loginViewModel.PasswordErrorMessage = loginResponse.Errors.PasswordError;
                        _loginViewModel.ErrorMessage = loginResponse.Errors.GeneralError;
                    }

                }
                else
                {
                    ErrorResponse errorResponse = responseInfo.ErrorResponse;
                    _loginViewModel.ErrorMessage = "SERVER ERROR: " + errorResponse.Message;
                }
            }
            catch (Exception ex)
            {
                _loginViewModel.ErrorMessage = $"Login failed: {ex.Message}";
            }
        }

    }
}
