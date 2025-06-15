using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Stores;
using ClientApp.ViewModels.ForgotPassword;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Commands
{
    class SubmitPasswordResetEmailCommand : CommandBase
    {
        private readonly RequestsExchangeService _requestsExchangeService;
        private readonly INavigationService _navigationService;
        private PasswordResetStore _state;
        private EmailEntryViewModel _emailEntryViewModel;

        /// <summary>
        /// Initializes the ViewModel, setting up the command for submitting the email.
        /// </summary>
        public SubmitPasswordResetEmailCommand(
            EmailEntryViewModel emailEntryViewModel,
            INavigationService navigationService,
            PasswordResetStore state,
            RequestsExchangeService requestsExchangeService)
        {
            this._emailEntryViewModel = emailEntryViewModel;
            _navigationService = navigationService;
            _requestsExchangeService = requestsExchangeService;
            _state = state;
        }

        /// <summary>
        /// Submits the entered email address to initiate the password recovery process. 
        /// If the email is valid, the process moves to the next step; otherwise, an error message is displayed.
        /// </summary>
        public override async void Execute(object parameters)
        {
            string trimmedEmail = this._state.Email?.Trim();

            // Ensure email is not empty
            if (string.IsNullOrEmpty(trimmedEmail))
            {
                _emailEntryViewModel.ErrorMessage = "Email field cannot be empty";
                return;
            }

            // Create request for password reset with the entered email
            ForgotPasswordRequest request = new ForgotPasswordRequest(trimmedEmail);
            ResponseInfo<PasswordResetCodeResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<PasswordResetCodeResponse>(request);

            // Handle potential error response
            if (responseInfo.NormalResponse)
            {
                // Process the response and move to the next step
                PasswordResetCodeResponse response = responseInfo.Response;
                if (response.Status == 0)
                {
                    this._navigationService.NavigateTo<CodeEntryViewModel>();
                }
                else
                {
                    _emailEntryViewModel.ErrorMessage = response.Errors.EmailError;
                }
            }

             
        }
    }
}
