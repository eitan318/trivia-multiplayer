using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Stores;
using ClientApp.ViewModels;
using ClientApp.ViewModels.ForgotPassword;

namespace ClientApp.Commands
{
    class ResetPasswordCommand : CommandBase
    {
        private ResetPasswordViewModel _resetPasswordViewModel;
        private readonly RequestsExchangeService _requestsExchangeService;
        private readonly INavigationService _navigationService;
        private PasswordResetStore _state;

        public ResetPasswordCommand(
            ResetPasswordViewModel resetPasswordViewModel,
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService,    
            PasswordResetStore state)
        {
            _navigationService = navigationService;
            _requestsExchangeService = requestsExchangeService;
            _state = state;
        }

         /// <summary>
        /// Handles the logic of resetting the password. It verifies that the new password and confirmation match,
        /// then sends a reset password request to the server. If successful, navigates to the login page.
        /// If there are errors, an appropriate error message is displayed.
        /// </summary>
        public override async void Execute(object parameters)
        {
            string trimmedNewPassword = _resetPasswordViewModel.NewPassword?.Trim();
            string trimmedConfirmPassword = _resetPasswordViewModel.ConfirmPassword?.Trim();

            // Ensure the new password and confirmation password match
            if (trimmedNewPassword != trimmedConfirmPassword)
            {
                _resetPasswordViewModel.ErrorMessage = "Need to be the same";
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
                    _resetPasswordViewModel.ErrorMessage = response.Errors.GeneralError;
                    _resetPasswordViewModel.NewPasswordErrorMessage = response.Errors.NewPasswordError;
                }

            }
            else
            {
                _resetPasswordViewModel.ErrorMessage = responseInfo.ErrorResponse.Message;
            }
        }
    }
}
