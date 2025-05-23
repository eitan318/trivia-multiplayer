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
        private readonly INavigationService _navigationService;
        private UserStore _userStore;
        private readonly RequestsExchangeService _requestsExchangeService;
        public SignupViewModel(
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService,
            UserStore userStore)
        {
            _navigationService = navigationService;
            this._userStore = userStore;
            this._navigationService = navigationService;

            // Initialize commands for different actions
            SignupCmd = new RelayCommand(PerformSignup);
            NavToLoginCmd = new NavigateCommand<LoginViewModel>(navigationService);
        }



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
                ((RelayCommand)SignupCmd).RaiseCanExecuteChanged();
            }
        }


        public string Password
        {
            get => _password;
            set
            {
                _password = value;
                OnPropertyChanged();
                ((RelayCommand)SignupCmd).RaiseCanExecuteChanged();
            }
        }

        public string Email
        {
            get => _email;
            set
            {
                _email = value;
                OnPropertyChanged();
                ((RelayCommand)SignupCmd).RaiseCanExecuteChanged();
            }
        }

        public string PhoneNumber
        {
            get => _phoneNumber;
            set
            {
                _phoneNumber = value;
                OnPropertyChanged();
                ((RelayCommand)SignupCmd).RaiseCanExecuteChanged();
            }
        }

        public string HouseAddress
        {
            get => _houseAddress;
            set
            {
                _houseAddress = value;
                OnPropertyChanged();
                ((RelayCommand)SignupCmd).RaiseCanExecuteChanged();
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
                    ((RelayCommand)SignupCmd).RaiseCanExecuteChanged();
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



        // Commands definition
        public ICommand SignupCmd { get; }
        public ICommand NavToLoginCmd { get; }


        /// <summary>
        /// Attempts to sign up the user by validating the input fields and sending the signup request.
        /// If the signup is successful, navigates to the login page. If there are errors, displays error messages.
        /// </summary>
        private async void PerformSignup()
        {
            const string cannotBeEmptyString = "Cannot be empty";

            // Reset error messages
            ErrorMessage = "";
            UsernameErrorMessage = "";
            PasswordErrorMessage = "";
            EmailErrorMessage = "";
            PhoneNumberErrorMessage = "";
            HouseAddressErrorMessage = "";
            BirthDateErrorMessage = "";

            bool requiredNotEmpty = true;

            // Trim input values
            string trimmedUsername = Username?.Trim();
            string trimmedPassword = Password?.Trim();
            string trimmedEmail = Email?.Trim();
            string trimmedPhoneNumber = PhoneNumber?.Trim();
            string trimmedHouseAddress = HouseAddress?.Trim();
            string trimmedBirthDate = BirthDate?.ToString("dd/MM/yyyy")??"";


            // Validate each field
            if (string.IsNullOrWhiteSpace(Username))
            {
                UsernameErrorMessage = cannotBeEmptyString;
                requiredNotEmpty = false;
            }

            if (string.IsNullOrWhiteSpace(Password))
            {
                PasswordErrorMessage = cannotBeEmptyString;
                requiredNotEmpty = false;
            }

            if (string.IsNullOrWhiteSpace(Email))
            {
                EmailErrorMessage = cannotBeEmptyString;
                requiredNotEmpty = false;
            }

            try
            {
                // Prepare the signup request and send it
                SignupRequest signupRequest = new SignupRequest(
                        trimmedUsername,
                        trimmedPassword,
                        trimmedEmail,
                        trimmedPhoneNumber,
                        trimmedHouseAddress,
                        trimmedBirthDate
                    );

                ResponseInfo responseInfo = await _requestsExchangeService.ExchangeRequest(signupRequest);

                // Handle server error response
                if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
                {
                    ErrorResponse errorResponse = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
                    ErrorMessage = "SERVER ERROR: " + errorResponse.Message;
                }
                else
                {
                    SignupResponse signupResponse = JsonResponseDeserialize.DeserializeResponse<SignupResponse>(responseInfo);
                    if(signupResponse.Status == 0 && requiredNotEmpty)
                    {
                        // Navigate to the login page upon successful signup
                        this._navigationService.NavigateTo<LoginViewModel>();
                    }
                    else
                    {
                        if(UsernameErrorMessage == "")
                            UsernameErrorMessage = signupResponse.Errors.UsernameError;
                        if (PasswordErrorMessage == "") 
                            PasswordErrorMessage = signupResponse.Errors.PasswordError;
                        if (EmailErrorMessage == "")
                            EmailErrorMessage = signupResponse.Errors.EmailError;
                        HouseAddressErrorMessage = signupResponse.Errors.HouseAddressError;
                        PhoneNumberErrorMessage = signupResponse.Errors.PhoneNumberError;
                        BirthDateErrorMessage = signupResponse.Errors.BirthDateError;
                    }
                }
            }
            catch (Exception ex)
            {
                ErrorMessage = $"Signup failed (sent from client side): {ex.Message}";
            }
        }
    }
}
