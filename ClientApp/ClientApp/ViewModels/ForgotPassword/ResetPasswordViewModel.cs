using ClientApp.Commands;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Stores;
using ClientApp.Views;
using System.Windows.Input;

namespace ClientApp.ViewModels.ForgotPassword
{
    /// <summary>
    /// ViewModel that handles the reset password step in the forgot password process.
    /// It manages user inputs for the new password, confirms it, and sends the reset password request.
    /// </summary>
    class ResetPasswordViewModel : ViewModelBase
    {
        private readonly RequestsExchangeService _requestsExchangeService;
        private readonly INavigationService _navigationService;
        private PasswordResetStore _state;

        public ResetPasswordViewModel(
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService,
            PasswordResetStore state) : base(true)
        {
            _navigationService = navigationService;
            _requestsExchangeService = requestsExchangeService;
            _state = state;
            ResetPasswordCmd = new RelayCommand(OnResetPassword);
        }

        // Password resert fields
        private string _newPassword;
        private string _confirmPassword;
        
        // Error fields
        private string _errorMessage;
        private string _newPasswordErrorMessage;


        // Password reset properties
        public string NewPassword
        {
            get => _newPassword;
            set
            { 
                _newPassword = value; 
                OnPropertyChanged();
            }
        }


        public string ConfirmPassword
        {
            get => _confirmPassword;
            set 
            { 
                _confirmPassword = value;
                OnPropertyChanged();
            }
        }


        //Error messages properties
        public string ErrorMessage
        {
            get => _errorMessage;
            set 
            { 
                _errorMessage = value; 
                OnPropertyChanged(); 
            }
        }

        public string NewPasswordErrorMessage
        {
            get => _newPasswordErrorMessage;
            set
            { 
                _newPasswordErrorMessage = value; 
                OnPropertyChanged(); 
            }
        }




        // Commands
        public ICommand ResetPasswordCmd { get; }



        /// <summary>
        /// Handles the logic of resetting the password. It verifies that the new password and confirmation match,
        /// then sends a reset password request to the server. If successful, navigates to the login page.
        /// If there are errors, an appropriate error message is displayed.
        /// </summary>
        private async void OnResetPassword()
        {
            string trimmedNewPassword = NewPassword?.Trim();
            string trimmedConfirmPassword = ConfirmPassword?.Trim();

            // Ensure the new password and confirmation password match
            if (trimmedNewPassword != trimmedConfirmPassword)
            {
                ErrorMessage = "Need to be the same";
                return;
            }

            // Create the request with the new password and username
            ResetPasswordRequest request = new ResetPasswordRequest(trimmedNewPassword, _state.Email, _state.Tocken);
            ResponseInfo<ResetPasswordResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<ResetPasswordResponse>(request);

            // Handle server error response
            if (responseInfo.NormalResponse)
            {
                // Handle successful response
                ResetPasswordResponse response = responseInfo.Response;
                if(response.Status == 0)
                {
                    // Navigate to the login page upon successful password reset
                    _navigationService.NavigateTo<LoginViewModel>();
                }
                else
                {
                    this.ErrorMessage = response.Errors.GeneralError;
                    this.NewPasswordErrorMessage = response.Errors.NewPasswordError;
                }

            }
            else
            {
                this.ErrorMessage = responseInfo.ErrorResponse.Message;
            }



        }
    }
}
