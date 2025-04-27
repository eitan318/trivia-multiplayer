using ClientApp.Commands;
using ClientApp.Enums;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Views;
using System.Windows.Input;

namespace ClientApp.ViewModels.ForgotPassword
{
    /// <summary>
    /// ViewModel that handles the reset password step in the forgot password process.
    /// It manages user inputs for the new password, confirms it, and sends the reset password request.
    /// </summary>
    class ResetPasswordStepViewModel : BaseViewModel
    {
        /// <summary>
        /// The new password entered by the user for password reset.
        /// </summary>
        private string _newPassword;
        public string NewPassword
        {
            get => _newPassword;
            set { _newPassword = value; OnPropertyChanged(); }
        }

        /// <summary>
        /// The confirmation password entered by the user to match with the new password.
        /// </summary>
        private string _confirmPassword;
        public string ConfirmPassword
        {
            get => _confirmPassword;
            set { _confirmPassword = value; OnPropertyChanged(); }
        }

        /// <summary>
        /// Error message to display if there are issues with the reset process.
        /// </summary>
        private string _errorMessage;
        public string ErrorMessage
        {
            get => _errorMessage;
            set { _errorMessage = value; OnPropertyChanged(); }
        }

        

        private string _newPasswordErrorMessage;
        public string NewPasswordErrorMessage
        {
            get => _newPasswordErrorMessage;
            set { _newPasswordErrorMessage = value; OnPropertyChanged(); }
        }

        /// <summary>
        /// The username associated with the password reset request.
        /// </summary>
        public string Username { get; set; }

        /// <summary>
        /// Command that triggers the password reset process.
        /// </summary>
        public ICommand ResetPasswordCommand { get; }

        /// <summary>
        /// Initializes the ViewModel with the reset password command.
        /// </summary>
        public ResetPasswordStepViewModel()
        {
            ResetPasswordCommand = new RelayCommand(OnResetPassword);
        }

        /// <summary>
        /// Handles the logic of resetting the password. It verifies that the new password and confirmation match,
        /// then sends a reset password request to the server. If successful, navigates to the login page.
        /// If there are errors, an appropriate error message is displayed.
        /// </summary>
        private async void OnResetPassword()
        {
            // Ensure the new password and confirmation password match
            if (NewPassword != ConfirmPassword)
            {
                ErrorMessage = "Need to be the same";
                return;
            }

            // Create the request with the new password and username
            ResetPasswordRequest request = new ResetPasswordRequest(NewPassword, Username);
            ResponseInfo responseInfo = await RequestsExchangeService.ExchangeRequest(request);

            // Handle server error response
            if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
            {
                ErrorResponse errorResponse = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
                this.ErrorMessage = errorResponse.Message;
                return;
            }

            // Handle successful response
            ResetPasswordResponse response = JsonResponseDeserialize.DeserializeResponse<ResetPasswordResponse>(responseInfo);
            if(response.Status == 0)
            {
                // Navigate to the login page upon successful password reset
                MyNavigationService.Navigate(new LoginPage());
            }
            else
            {
                this.ErrorMessage = response.Errors.GeneralError;
                this.NewPasswordErrorMessage = response.Errors.NewPasswordError;
            }

        }
    }
}
