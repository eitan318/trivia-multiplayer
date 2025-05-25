using ClientApp.Services;
using ClientApp.Commands;
using System.Windows.Input;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Stores;

namespace ClientApp.ViewModels
{
    class SignupViewModel : ViewModelBase
    {
        private UserStore _userStore;
        public SignupViewModel(
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService,
            UserStore userStore)
        {
            this._userStore = userStore;

            // Initialize commands for different actions
            SignupCmd = new SignupCommand(this, navigationService, requestsExchangeService);
            NavToLoginCmd = new NavigateCommand<LoginViewModel>(navigationService);
        }


        // Commands definition
        public ICommand SignupCmd { get; }
        public ICommand NavToLoginCmd { get; }





        // Account fields
        private string _password = "";
        private string _email = "";
        private string _houseAddress = "";
        private string _phoneNumber = "";
        private DateTime? _birthDate;

        // Error message fields
        private string _usernameErrorMessage;
        private string _passwordErrorMessage;
        private string _emailErrorMessage;
        private string _phoneNumberErrorMessage;
        private string _houseAddressErrorMessage;
        private string _birthDateErrorMessage;

        private string _errorMessage;



        public string Username
        {
            get => _userStore.Username??"";
            set
            {
                _userStore.Username = value;
                OnPropertyChanged();
                ((CommandBase)SignupCmd).RaiseCanExecuteChanged();
            }
        }


        public string Password
        {
            get => _password;
            set
            {
                _password = value;
                OnPropertyChanged();
                ((CommandBase)SignupCmd).RaiseCanExecuteChanged();
            }
        }

        public string Email
        {
            get => _email;
            set
            {
                _email = value;
                OnPropertyChanged();
                ((CommandBase)SignupCmd).RaiseCanExecuteChanged();
            }
        }

        public string PhoneNumber
        {
            get => _phoneNumber;
            set
            {
                _phoneNumber = value;
                OnPropertyChanged();
                ((CommandBase)SignupCmd).RaiseCanExecuteChanged();
            }
        }

        public string HouseAddress
        {
            get => _houseAddress;
            set
            {
                _houseAddress = value;
                OnPropertyChanged();
                ((CommandBase)SignupCmd).RaiseCanExecuteChanged();
            }
        }


        public DateTime? BirthDate
        {
            get => _birthDate;
            set
            {
                if (_birthDate != value)
                {
                    _birthDate = value?.Date;
                    OnPropertyChanged(nameof(BirthDate));
                    ((CommandBase)SignupCmd).RaiseCanExecuteChanged();
                }
            }
        }

        // Error messages properties

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

        public string EmailErrorMessage 
        {
            get => _emailErrorMessage;
            set
            {
                _emailErrorMessage = value;
                OnPropertyChanged();
            }
        }

        public string PhoneNumberErrorMessage 
        {
            get => _phoneNumberErrorMessage;
            set
            {
                _phoneNumberErrorMessage = value;
                OnPropertyChanged();
            }
        }

        public string HouseAddressErrorMessage 
        {
            get => _houseAddressErrorMessage;
            set
            {
                _houseAddressErrorMessage = value;
                OnPropertyChanged();
            }
        }

        public string BirthDateErrorMessage 
        {
            get => _birthDateErrorMessage;
            set
            {
                _birthDateErrorMessage = value;
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
