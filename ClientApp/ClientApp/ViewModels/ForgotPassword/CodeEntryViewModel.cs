using ClientApp.Commands;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Stores;
using System.Collections.ObjectModel;
namespace ClientApp.ViewModels.ForgotPassword
{
    /// <summary>
    /// ViewModel for the code input step in the forgot password process. Handles user input for the verification code
    /// and manages navigation between steps in the forgot password flow.
    /// </summary>
    class CodeEntryViewModel : ViewModelBase
    {
        INavigationService _navigationService;
        PasswordResetStore _state;


        
        /// <summary>
        /// Initializes the ViewModel, setting up the code boxes and the associated commands.
        /// </summary>
        /// <param name="parent">The parent ViewModel that controls the overall flow of the forgot password process.</param>
        public CodeEntryViewModel(INavigationService navigationService, PasswordResetStore state)
        {
            this._navigationService = navigationService;
            this._state = state;


            // Initialize 6 code boxes for user input
            CodeBoxes = new ObservableCollection<CodeBox>(
                Enumerable.Range(0, 6).Select(_ => new CodeBox()));

            // Setup commands for submitting the code and retrying the email verification
            SubmitCodeCmd = new RelayCommand(SubmitCode);
            RetryCmd = new RelayCommand(Retry);
        }

        // Error message field
        private string _errorMessage;

        // Error mesage property

        public string ErrorMessage
        {
            get => _errorMessage;
            set
            {
                _errorMessage = value;
                OnPropertyChanged();
            }
        }



        // Commands
        public RelayCommand SubmitCodeCmd { get; }
        public RelayCommand RetryCmd { get; }


        /// <summary>
        /// Collection of code boxes that represent the input fields for the verification code.
        /// </summary>
        public ObservableCollection<CodeBox> CodeBoxes { get; set; }


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
                    this._state.Tocken = response.PasswordResetTocken;
                    this._navigationService.NavigateTo<ResetPasswordViewModel>();
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
            _navigationService.NavigateTo<EmailEntryViewModel>();
        }
    }

    /// <summary>
    /// Represents a single input field for the verification code.
    /// </summary>
    public class CodeBox : ViewModelBase
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
