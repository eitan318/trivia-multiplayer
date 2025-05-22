using ClientApp.Commands;
using ClientApp.Services;
using System.Windows.Input;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Views.States;
using System.Windows.Navigation;

namespace ClientApp.ViewModels.ForgotPassword
{
    /// <summary>
    /// ViewModel for the email input step in the forgot password process. Handles the user's input of their email address
    /// and processes the request to initiate the password recovery process.
    /// </summary>
    class EmailEntryViewModel : ViewModelBase
    {
        INavigationService _navigationService;
        PasswordResetState _state;

        /// <summary>
        /// Initializes the ViewModel, setting up the command for submitting the email.
        /// </summary>
        public EmailEntryViewModel(INavigationService navigationService, PasswordResetState state)
        {
            _navigationService = navigationService;
            _state = state;
            SubmitEmailCmd = new RelayCommand(SubmitEmail);
        }

        // Error fields
        private string _errorMessage;


        //Email Property
        public string Email
        {
            get => _state.Email;
            set
            {
                _state.Email = value;
                OnPropertyChanged();
            }
        }

        // Error properties
        public string ErrorMessage
        {
            get => _errorMessage;
            set 
            { 
                _errorMessage = value; 
                OnPropertyChanged();
            }
        }

        //Commands
        public ICommand SubmitEmailCmd { get; }



        /// <summary>
        /// Submits the entered email address to initiate the password recovery process. 
        /// If the email is valid, the process moves to the next step; otherwise, an error message is displayed.
        /// </summary>
        private async void SubmitEmail()
        {
            string trimmedEmail = this._state.Email?.Trim();

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
                this._navigationService.NavigateTo<CodeEntryViewModel>();
            }
            else
            {
                ErrorMessage = response.Errors.EmailError;
            }
        }
    }
}
