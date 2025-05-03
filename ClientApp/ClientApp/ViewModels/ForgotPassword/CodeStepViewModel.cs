using ClientApp.Commands;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

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
        /// The target code sent to the user's email that needs to be entered correctly.
        /// </summary>
        public string TargetEmailCode { get; set; }

        /// <summary>
        /// The username associated with the account that is undergoing the password reset process.
        /// </summary>
        public string Username { get; set; }

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
        private void SubmitCode()
        {
            // Concatenate all values from the code boxes and process the code
            var code = string.Concat(CodeBoxes.Select(box => box.Value));
            if (code != this.TargetEmailCode)
            {
                ErrorMessage = "Wrong code";
                return;
            }
            _parent.GoToResetPasswordStep(Username);
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
