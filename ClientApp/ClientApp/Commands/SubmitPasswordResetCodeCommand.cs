using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Stores;
using ClientApp.ViewModels.ForgotPassword;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Commands
{
    public class SubmitPasswordResetCodeCommand : CommandBase, IAsyncCommand
    {
        private readonly INavigationService _navigationService;
        private readonly RequestsExchangeService _requestsExchangeService;
        private PasswordResetStore _state;



        /// <summary>
        /// Initializes the ViewModel, setting up the code boxes and the associated commands.
        /// </summary>
        public SubmitPasswordResetCodeCommand(
            INavigationService navigationService,
            PasswordResetStore state,
            RequestsExchangeService requestsExchangeService)
        {
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService;
            this._state = state;
        }

        /// <summary>
        /// Submits the entered verification code. If the code is correct, it proceeds to the password reset step.
        /// If the code is incorrect, an error message is displayed.
        /// </summary>
        public override async Task ExecuteAsync(object parameters) 
        {
            if(parameters is not CodeEntryViewModel codeEntryViewModel)
            {
                return;
            }
            // Concatenate all values from the code boxes and process the code
            var code = string.Concat(codeEntryViewModel.CodeBoxes.Select(box => box.Value));
            VerifyPasswordResetCodeRequest request = new VerifyPasswordResetCodeRequest(code);
            ResponseInfo<VerifyPasswordResetCodeResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<VerifyPasswordResetCodeResponse>(request);
            if (responseInfo.NormalResponse)
            {
                VerifyPasswordResetCodeResponse response = responseInfo.Response;
                if (response.Status == 0)
                {
                    this._state.Tocken = response.PasswordResetTocken;
                    this._navigationService.NavigateTo<ResetPasswordViewModel>();
                }
                else
                {
                    codeEntryViewModel.ErrorMessage = response.Errors.GeneralError;
                }

            }
        }


    }
}
