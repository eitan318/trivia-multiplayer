using ClientApp.Commands;
using System.Windows.Input;

namespace ClientApp.ViewModels.ForgotPassword
{
    /// <summary>
    /// Command that does the reset password step in the forgot password process.
    /// </summary>
    public class ResetPasswordViewModel : ScreenViewModelBase
    {
        public ResetPasswordViewModel(
            ResetPasswordCommand resetPasswordCommand) : base(true)
        {
            ResetPasswordCmd = resetPasswordCommand;
        }


        // Commands
        public ICommand ResetPasswordCmd { get; }


        // Password resert fields
        private string _newPassword;
        private string _confirmPassword;
        
        // Error fields
        private string _errorMessage;
        private string _newPasswordErrorMessage;


        // Password reset properties
        public string NewPassword
        {
            get => _newPassword;
            set
            { 
                _newPassword = value; 
                OnPropertyChanged();
            }
        }


        public string ConfirmPassword
        {
            get => _confirmPassword;
            set 
            { 
                _confirmPassword = value;
                OnPropertyChanged();
            }
        }


        //Error messages properties
        public string ErrorMessage
        {
            get => _errorMessage;
            set 
            { 
                _errorMessage = value; 
                OnPropertyChanged(); 
            }
        }

        public string NewPasswordErrorMessage
        {
            get => _newPasswordErrorMessage;
            set
            { 
                _newPasswordErrorMessage = value; 
                OnPropertyChanged(); 
            }
        }

    }
}
