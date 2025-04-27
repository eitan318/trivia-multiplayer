using ClientApp.Enums;
using ClientApp.Commands;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.ViewModels.ClientApp.ViewModels;
using ClientApp.Views;
using ClientApp.Views.Pages;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Input;
using ClientApp.Models;

namespace ClientApp.ViewModels
{
    /// <summary>
    /// ViewModel for handling user authentication operations including login, signup, and navigation.
    /// </summary>
    class AuthenticationViewModel : BaseViewModel
    {
        private AuthenticationViewModel()
        {
            // Initialize commands for different actions
            SignupCommand = new RelayCommand(PerformSignup);
            NavigateToLoginCommand = new RelayCommand(NavigateToLogin);
            LoginCommand = new RelayCommand(PerformLogin, CanPerformLogin);
            NavigateToSignupCommand = new RelayCommand(NavigateToSignup);
            NavigateToForgotPasswordCommand = new RelayCommand(NavigateToForgotPassword);
        }

        /// <summary>
        /// Provides a singleton instance of the <see cref="AuthenticationViewModel"/>.
        /// </summary>
        public static AuthenticationViewModel Instance()
        {
            return GetInstance(() => new AuthenticationViewModel());

        }
        private string _password;
        private string _username;
        private string _email;
        private string _houseAddress;
        private string _phoneNumber;
        private string _birthDate;

        private string _usernameErrorMessage;
        private string _passwordErrorMessage;
        private string _emailErrorMessage;
        private string _phoneNumberErrorMessage;
        private string _houseAddressErrorMessage;
        private string _birthDateErrorMessage;

        private string _errorMessage;

        // Properties for username, password, email, etc., with change notification
        public string Username
        {
            get => _username;
            set
            {
                _username = value;
                OnPropertyChanged();
                ((RelayCommand)LoginCommand).RaiseCanExecuteChanged();
                ((RelayCommand)SignupCommand).RaiseCanExecuteChanged();
            }
        }

        public string Password
        {
            get => _password;
            set
            {
                _password = value;
                OnPropertyChanged();
                ((RelayCommand)LoginCommand).RaiseCanExecuteChanged();
                ((RelayCommand)SignupCommand).RaiseCanExecuteChanged();
            }
        }

        public string Email
        {
            get => _email;
            set
            {
                _email = value;
                OnPropertyChanged();
                ((RelayCommand)SignupCommand).RaiseCanExecuteChanged();
            }
        }

        public string PhoneNumber
        {
            get => _phoneNumber;
            set
            {
                _phoneNumber = value;
                OnPropertyChanged();
                ((RelayCommand)SignupCommand).RaiseCanExecuteChanged();
            }
        }

        public string HouseAddress
        {
            get => _houseAddress;
            set
            {
                _houseAddress = value;
                OnPropertyChanged();
                ((RelayCommand)SignupCommand).RaiseCanExecuteChanged();
            }
        }

        public string BirthDate
        {
            get => _birthDate;
            set
            {
                _birthDate = value;
                OnPropertyChanged();
                ((RelayCommand)SignupCommand).RaiseCanExecuteChanged();
            }
        }

        // Error message properties
        public string UsernameErrorMessage { get => _usernameErrorMessage; set { _usernameErrorMessage = value; OnPropertyChanged(); } }
        public string PasswordErrorMessage { get => _passwordErrorMessage; set { _passwordErrorMessage = value; OnPropertyChanged(); } }
        public string EmailErrorMessage { get => _emailErrorMessage; set { _emailErrorMessage = value; OnPropertyChanged(); } }
        public string PhoneNumberErrorMessage { get => _phoneNumberErrorMessage; set { _phoneNumberErrorMessage = value; OnPropertyChanged(); } }
        public string HouseAddressErrorMessage { get => _houseAddressErrorMessage; set { _houseAddressErrorMessage = value; OnPropertyChanged(); } }
        public string BirthDateErrorMessage { get => _birthDateErrorMessage; set { _birthDateErrorMessage = value; OnPropertyChanged(); } }
        public string ErrorMessage { get => _errorMessage; set { _errorMessage = value; OnPropertyChanged(); } }

        // Commands for different actions
        public ICommand SignupCommand { get; }
        public ICommand LoginCommand { get; }
        public ICommand NavigateToForgotPasswordCommand { get; }
        public ICommand NavigateToLoginCommand { get; }
        public ICommand NavigateToSignupCommand { get; }

        // Method to navigate to the signup page
        private void NavigateToSignup()
        {
            ErrorMessage = "";
            UsernameErrorMessage = "";
            PasswordErrorMessage = "";
            EmailErrorMessage = "";
            PhoneNumberErrorMessage = "";
            HouseAddressErrorMessage = "";
            BirthDateErrorMessage = "";
            MyNavigationService.Navigate(new SignupPage());
        }

        // Method to navigate to the forgot password page
        private void NavigateToForgotPassword()
        {
            MyNavigationService.Navigate(new ForgotPasswordPage(new LoginPage()));
        }



        private bool CanPerformLogin()
        {
            return !string.IsNullOrWhiteSpace(Username) &&
                !string.IsNullOrWhiteSpace(Password);
        }

        /// <summary>
        /// Attempts to log in the user by validating the username and password.
        /// If successful, navigates to the menu page. If there is an error, shows the error messages.
        /// </summary>
        private async void PerformLogin()
        {
            ErrorMessage = "";
            UsernameErrorMessage = "";
            PasswordErrorMessage = "";

            try
            {
                // Prepare the login request and send it
                LoginRequest loginRequest = new LoginRequest(Username, Password);
                ResponseInfo responseInfo = await RequestsExchangeService.ExchangeRequest(loginRequest);

                // Handle server error response
                if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
                {
                    ErrorResponse errorResponse = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
                    ErrorMessage = "SERVER ERROR: " + errorResponse.Message;
                }
                else
                {
                    LoginResponse loginResponse = JsonResponseDeserialize.DeserializeResponse<LoginResponse>(responseInfo);
                    if(loginResponse.Status == 0)
                    {
                        MyNavigationService.Navigate(new MenuPage());
                    }
                    else
                    {
                        UsernameErrorMessage = loginResponse.Errors.UsernameError;
                        PasswordErrorMessage= loginResponse.Errors.PasswordError;
                    }

                }
            }
            catch (Exception ex)
            {
                ErrorMessage = $"Login failed (sent from client side): {ex.Message}";
            }
        }

        // Method to navigate to the login page
        private void NavigateToLogin()
        {
            ErrorMessage = "";
            UsernameErrorMessage = "";
            PasswordErrorMessage = "";
            MyNavigationService.Navigate(new LoginPage());
        }

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

            bool perform = true;

            // Validate each field
            if (string.IsNullOrWhiteSpace(Username))
            {
                UsernameErrorMessage = cannotBeEmptyString;
                perform = false;
            }

            if (string.IsNullOrWhiteSpace(Password))
            {
                PasswordErrorMessage = cannotBeEmptyString;
                perform = false;
            }

            if (string.IsNullOrWhiteSpace(Email))
            {
                EmailErrorMessage = cannotBeEmptyString;
                perform = false;
            }

            if (string.IsNullOrWhiteSpace(PhoneNumber))
            {
                PhoneNumberErrorMessage = cannotBeEmptyString;
                perform = false;
            }

            if (string.IsNullOrWhiteSpace(HouseAddress))
            {
                HouseAddressErrorMessage = cannotBeEmptyString;
                perform = false;
            }

            if (string.IsNullOrWhiteSpace(BirthDate))
            {
                BirthDateErrorMessage = cannotBeEmptyString;
                perform = false;
            }

            // If any field is invalid, prevent further action
            if (!perform)
            {
                return;
            }


            try
            {
                // Prepare the signup request and send it
                SignupRequest signupRequest = new SignupRequest(Username, Password, Email, PhoneNumber, HouseAddress, BirthDate);

                ResponseInfo responseInfo = await RequestsExchangeService.ExchangeRequest(signupRequest);

                // Handle server error response
                if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
                {
                    ErrorResponse errorResponse = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
                    ErrorMessage = "SERVER ERROR: " + errorResponse.Message;
                }
                else
                {
                    SignupResponse signupResponse = JsonResponseDeserialize.DeserializeResponse<SignupResponse>(responseInfo);
                    if(signupResponse.Status == 0)
                    {
                        // Navigate to the login page upon successful signup
                        MyNavigationService.Navigate(new LoginPage());
                    }
                    else
                    {
                        UsernameErrorMessage = signupResponse.Errors.UsernameError;
                        PasswordErrorMessage = signupResponse.Errors.PasswordError;
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
