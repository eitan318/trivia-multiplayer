using ClientApp.Commands;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using System.Collections.ObjectModel;
namespace ClientApp.ViewModels.ForgotPassword
{
    /// <summary>
    /// ViewModel for the code input step in the forgot password process. Handles user input for the verification code
    /// and manages navigation between steps in the forgot password flow.
    /// </summary>
    class CodeStepViewModel : BaseViewModel
    {
        /// <summary>
        /// The parent ViewModel that controls the overall flow of the forgot password process.
        /// </summary>
        private readonly ForgotPasswordViewModel _parent;

        /// <summary>
        /// Error message to display when the user enters an incorrect code.
        /// </summary>
        private string _errorMessage;
        public string ErrorMessage
        {
            get => _errorMessage;
            set { _errorMessage = value; OnPropertyChanged(); }
        }

        /// <summary>
        /// Collection of code boxes that represent the input fields for the verification code.
        /// </summary>
        public ObservableCollection<CodeBox> CodeBoxes { get; set; }

        /// <summary>
        /// The username associated with the account that is undergoing the password reset process.
        /// </summary>
        public string Email { get; set; }

        /// <summary>
        /// Command to submit the entered code.
        /// </summary>
        public RelayCommand SubmitCodeCommand { get; }

        /// <summary>
        /// Command to retry the email verification step in case of an error.
        /// </summary>
        public RelayCommand RetryCommand { get; }

        /// <summary>
        /// Initializes the ViewModel, setting up the code boxes and the associated commands.
        /// </summary>
        /// <param name="parent">The parent ViewModel that controls the overall flow of the forgot password process.</param>
        public CodeStepViewModel(ForgotPasswordViewModel parent)
        {
            this._parent = parent;

            // Initialize 6 code boxes for user input
            CodeBoxes = new ObservableCollection<CodeBox>(
                Enumerable.Range(0, 6).Select(_ => new CodeBox()));

            // Setup commands for submitting the code and retrying the email verification
            SubmitCodeCommand = new RelayCommand(SubmitCode);
            RetryCommand = new RelayCommand(Retry);
        }

        /// <summary>
        /// Submits the entered verification code. If the code is correct, it proceeds to the password reset step.
        /// If the code is incorrect, an error message is displayed.
        /// </summary>
        private async void SubmitCode()
        {
            // Concatenate all values from the code boxes and process the code
            var code = string.Concat(CodeBoxes.Select(box => box.Value));
            VerifyPasswordResetCodeRequest request = new VerifyPasswordResetCodeRequest(code);
            ResponseInfo responseInfo = await RequestsExchangeService.ExchangeRequest(request);
            if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
            {
                ErrorResponse errorResponse = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
                ErrorMessage = "SERVER ERROR: " + errorResponse.Message;
            }
            else
            {
                VerifyPasswordResetCodeResponse response = JsonResponseDeserialize.DeserializeResponse<VerifyPasswordResetCodeResponse>(responseInfo);
                if (response.Status == 0)
                {
                    _parent.GoToResetPasswordStep(Email, response.PasswordResetTocken);
                }
                else
                {
                    ErrorMessage = response.Errors.GeneralError;
                }
            }

        }

        /// <summary>
        /// Retries the email verification step, going back to the email input step.
        /// </summary>
        private void Retry()
        {
            _parent.GoToEmailStep();
        }
    }

    /// <summary>
    /// Represents a single input field for the verification code.
    /// </summary>
    public class CodeBox : BaseViewModel
    {
        /// <summary>
        /// The value entered by the user in the code input field.
        /// </summary>
        private string _value;
        public string Value
        {
            get => _value;
            set { _value = value; OnPropertyChanged(); }
        }
    }
}
