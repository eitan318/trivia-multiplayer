using ClientApp.Services;
using ClientApp.Commands;
using System.Windows.Input;
using ClientApp.ViewModels.ForgotPassword;
using ClientApp.Stores;

namespace ClientApp.ViewModels
{
    class LoginViewModel : ViewModelBase
    {
        private UserStore _userStore;
        
        public LoginViewModel(
            INavigationService navigationService,
            UserStore userStore,
            RequestsExchangeService requestsExchangeService)
        {
            this._userStore = userStore;

            // Initialize commands for different actions
            LoginCmd = new LoginCommand(this, navigationService, userStore, requestsExchangeService);
            NavToSignupCmd = new NavigateCommand<SignupViewModel>(navigationService);
            NavToForgotPasswordCmd = new NavigateCommand<EmailEntryViewModel>(navigationService);

        }

        // Commands
        public ICommand LoginCmd { get; }
        public ICommand NavToSignupCmd { get; }
        public ICommand NavToForgotPasswordCmd { get; }



        //Fields for account
        private string _password = "";
         
        //Fields for error messages
        private string _errorMessage;
        private string _usernameErrorMessage;
        private string _passwordErrorMessage;

        
        // Properties for account
        public string Username
        {
            get => _userStore.Username??"";
            set
            {
                _userStore.Username = value;
                OnPropertyChanged();
                ((CommandBase)LoginCmd).RaiseCanExecuteChanged();
            }
        }

        public string Password
        {
            get => _password;
            set
            {
                _password = value;
                OnPropertyChanged();
                ((CommandBase)LoginCmd).RaiseCanExecuteChanged();
            }
        }


        //Error messages properties

        public string UsernameErrorMessage 
        { 
            get => _usernameErrorMessage;
            set 
            {
                _usernameErrorMessage = value;
                OnPropertyChanged(); 
            }
        }
        public string PasswordErrorMessage 
        { 
            get => _passwordErrorMessage;
            set 
            { 
                _passwordErrorMessage = value;
                OnPropertyChanged(); 
            }
        }

        public string ErrorMessage
        {
            get => _errorMessage;
            set
            { 
                _errorMessage = value;
                OnPropertyChanged();
            }
        }




        
    }
}
