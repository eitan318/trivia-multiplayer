using ClientApp.Commands;
using ClientApp.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;

namespace ClientApp.ViewModels.ForgotPassword
{
    /// <summary>
    /// ViewModel for the email input step in the forgot password process. Handles the user's input of their email address
    /// and processes the request to initiate the password recovery process.
    /// </summary>
    class EmailStepViewModel : BaseViewModel
    {
        /// <summary>
        /// The parent ViewModel that controls the overall flow of the forgot password process.
        /// </summary>
        private readonly ForgotPasswordViewModel _parent;

        /// <summary>
        /// Initializes the ViewModel, setting up the command for submitting the email.
        /// </summary>
        /// <param name="parent">The parent ViewModel that controls the overall flow of the forgot password process.</param>
        public EmailStepViewModel(ForgotPasswordViewModel parent)
        {
            _parent = parent;
            SubmitEmailCommand = new RelayCommand(SubmitEmail);
        }

        /// <summary>
        /// The email address entered by the user for the password recovery process.
        /// </summary>
        public string Email { get; set; }

        public ICommand SubmitEmailCommand { get; }

        /// <summary>
        /// Error message to display if there is an issue with the email input or response.
        /// </summary>
        private string _errorMessage;
        public string ErrorMessage
        {
            get => _errorMessage;
            set { _errorMessage = value; OnPropertyChanged(); }
        }

        /// <summary>
        /// Submits the entered email address to initiate the password recovery process. 
        /// If the email is valid, the process moves to the next step; otherwise, an error message is displayed.
        /// </summary>
        private async void SubmitEmail()
        {
            string trimmedEmail = Email?.Trim();

            // Ensure email is not empty
            if (string.IsNullOrEmpty(trimmedEmail))
            {
                ErrorMessage = "Email field cannot be empty";
                return;
            }

            // Create request for password reset with the entered email
            ForgotPasswordRequest request = new ForgotPasswordRequest(trimmedEmail);
            ResponseInfo responseInfo = await RequestsExchangeService.ExchangeRequest(request);

            // Handle potential error response
            if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
            {
                ErrorResponse errorResponse = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
                ErrorMessage = errorResponse.Message;
                return;
            }

            // Process the response and move to the next step
            PasswordResetCodeResponse response = JsonResponseDeserialize.DeserializeResponse<PasswordResetCodeResponse>(responseInfo);
            if (response.Status == 0)
            {
                _parent.GoToCodeStep(response.EmailCode, response.Username);
            }
            else
            {
                ErrorMessage = response.Errors.EmailError;
            }
        }
    }
}
