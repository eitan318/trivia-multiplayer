using ClientApp.Commands;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Stores;
using System.Collections.ObjectModel;
using System.Windows.Input;
namespace ClientApp.ViewModels.ForgotPassword
{
    /// <summary>
    /// ViewModel for the code input step in the forgot password process. Handles user input for the verification code
    /// and manages navigation between steps in the forgot password flow.
    /// </summary>
    public class CodeEntryViewModel : ScreenViewModelBase
    {
        
        /// <summary>
        /// Initializes the ViewModel, setting up the code boxes and the associated commands.
        /// </summary>
        /// <param name="parent">The parent ViewModel that controls the overall flow of the forgot password process.</param>
        public CodeEntryViewModel(
            SubmitPasswordResetCodeCommand submitCodeCommand) : base(true)
        {
            // Initialize 6 code boxes for user input
            CodeBoxes = new ObservableCollection<CodeBox>(
                Enumerable.Range(0, 6).Select(_ => new CodeBox()));

            // Setup commands for submitting the code and retrying the email verification
            SubmitCodeCmd = submitCodeCommand;
        }

        
        // Commands
        public ICommand SubmitCodeCmd { get; }


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

        /// <summary>
        /// Collection of code boxes that represent the input fields for the verification code.
        /// </summary>
        public ObservableCollection<CodeBox> CodeBoxes { get; set; }
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
