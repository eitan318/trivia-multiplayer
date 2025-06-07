using ClientApp.Services;
using ClientApp.Commands;
using System.Windows.Input;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.ViewModels.ForgotPassword;
using ClientApp.Stores;

namespace ClientApp.ViewModels
{
    class LoginViewModel : ViewModelBase
    {
        private readonly INavigationService _navigationService;
        private UserStore _userStore;
        private readonly RequestsExchangeService _requestsExchangeService;
        
        public LoginViewModel(
            INavigationService navigationService,
            UserStore userStore,
            RequestsExchangeService requestsExchangeService)
        {
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService;
            this._userStore = userStore;

            // Initialize commands for different actions
            LoginCmd = new RelayCommand(PerformLogin, CanPerformLogin);
            NavToSignupCmd = new NavigateCommand<SignupViewModel>(navigationService);
            NavToForgotPasswordCmd = new NavigateCommand<EmailEntryViewModel>(navigationService);

        }

        //Fields for account
        private string _password = "";
         
        //Fields for error messages
        private string _errorMessage;
        private string _usernameErrorMessage;
        private string _passwordErrorMessage;

        
        // Properties for account
        public string Username
        {
            get => _userStore.Username??"";
            set
            {
                _userStore.Username = value;
                OnPropertyChanged();
                ((RelayCommand)LoginCmd).RaiseCanExecuteChanged();
            }
        }

        public string Password
        {
            get => _password;
            set
            {
                _password = value;
                OnPropertyChanged();
                ((RelayCommand)LoginCmd).RaiseCanExecuteChanged();
            }
        }


        //Error messages properties

        public string UsernameErrorMessage 
        { 
            get => _usernameErrorMessage;
            set 
            {
                _usernameErrorMessage = value;
                OnPropertyChanged(); 
            }
        }
        public string PasswordErrorMessage 
        { 
            get => _passwordErrorMessage;
            set 
            { 
                _passwordErrorMessage = value;
                OnPropertyChanged(); 
            }
        }

        public string ErrorMessage
        {
            get => _errorMessage;
            set
            { 
                _errorMessage = value;
                OnPropertyChanged();
            }
        }


        public ICommand LoginCmd { get; }
        public ICommand NavToSignupCmd { get; }
        public ICommand NavToForgotPasswordCmd { get; }



        private bool CanPerformLogin()
        {
            return !string.IsNullOrWhiteSpace(Username) &&
                !string.IsNullOrWhiteSpace(Password);
        }

        /// <summary>
        /// Attempts to log in the user by validating the username and password.
        /// If successful, navigates to the menu page. If there is an error, shows the error messages.
        /// </summary>
        private async void PerformLogin()
        {
            ErrorMessage = "";
            UsernameErrorMessage = "";
            PasswordErrorMessage = "";

            try
            {
                // Trim input values
                string trimmedUsername = Username?.Trim();
                string trimmedPassword = Password?.Trim();

                this._userStore.Username = Username;

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
                        UsernameErrorMessage = loginResponse.Errors.UsernameError;
                        PasswordErrorMessage = loginResponse.Errors.PasswordError;
                        ErrorMessage = loginResponse.Errors.GeneralError;
                    }

                }
                else
                {
                    ErrorResponse errorResponse = responseInfo.ErrorResponse;
                    ErrorMessage = "SERVER ERROR: " + errorResponse.Message;
                }
            }
            catch (Exception ex)
            {
                ErrorMessage = $"Login failed: {ex.Message}";
            }
        }
    }
}
