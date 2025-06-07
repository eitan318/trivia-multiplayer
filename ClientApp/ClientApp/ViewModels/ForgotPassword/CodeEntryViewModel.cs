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
        private readonly INavigationService _navigationService;
        private readonly RequestsExchangeService _requestsExchangeService;
        private PasswordResetStore _state;


        
        /// <summary>
        /// Initializes the ViewModel, setting up the code boxes and the associated commands.
        /// </summary>
        /// <param name="parent">The parent ViewModel that controls the overall flow of the forgot password process.</param>
        public CodeEntryViewModel(
            INavigationService navigationService, 
            PasswordResetStore state,
            RequestsExchangeService requestsExchangeService) : base(true)
        {
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService;
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
                    ErrorMessage = response.Errors.GeneralError;
                }

            }
            else
            {
                ErrorResponse errorResponse = responseInfo.ErrorResponse;
                ErrorMessage = "SERVER ERROR: " + errorResponse.Message;
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
