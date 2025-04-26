using ClientApp.Commands;
using ClientApp.Enums;
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
            LoginCommand = new RelayCommand(PerformLogin);
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
        private string _passwordErrorMessage;
        private string _usernameErrorMessage;
        private string _errorMessage;

        // Properties for username, password, email, etc., with change notification
        public string Password { get => _password; set { _password = value; OnPropertyChanged(); } }
        public string Username { get => _username; set { _username = value; OnPropertyChanged(); } }
        public string Email { get => _email; set { _email = value; OnPropertyChanged(); } }
        public string PhoneNumber { get => _phoneNumber; set { _phoneNumber = value; OnPropertyChanged(); } }
        public string HouseAddress { get => _houseAddress; set { _houseAddress = value; OnPropertyChanged(); } }
        public string BirthDate { get => _birthDate; set { _birthDate = value; OnPropertyChanged(); } }

        // Error message properties
        public string PasswordErrorMessage { get => _passwordErrorMessage; set { _passwordErrorMessage = value; OnPropertyChanged(); } }
        public string UsernameErrorMessage { get => _usernameErrorMessage; set { _usernameErrorMessage = value; OnPropertyChanged(); } }
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
            MyNavigationService.Navigate(new SignupPage());
        }

        // Method to navigate to the forgot password page
        private void NavigateToForgotPassword()
        {
            MyNavigationService.Navigate(new ForgotPasswordPage(new LoginPage()));
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
            bool perform = true;
            if (string.IsNullOrWhiteSpace(Username))
            {
                UsernameErrorMessage = "Cannot be empty";
                perform = false;
            }
            if (string.IsNullOrWhiteSpace(Password))
            {
                PasswordErrorMessage = "Cannot be empty";
                perform = false;
            }

            if (!perform)
                return;

            try
            {
                // Prepare the login request and send it
                LoginRequest loginRequest = new LoginRequest
                {
                    Password = Password,
                    Username = Username,
                };

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
                    switch (loginResponse.Status)
                    {
                        case (byte)LoginResponseStatus.Success:
                            MyNavigationService.Navigate(new MenuPage());
                            break;
                        case (byte)LoginResponseStatus.UnknowenUsername:
                            UsernameErrorMessage = "username does not exist";
                            break;
                        case (byte)LoginResponseStatus.PasswordDoesntMatch:
                            PasswordErrorMessage = "password doesn't match username";
                            break;
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
            MyNavigationService.Navigate(new LoginPage());
        }

        /// <summary>
        /// Attempts to sign up the user by validating the input fields and sending the signup request.
        /// If the signup is successful, navigates to the login page. If there are errors, displays error messages.
        /// </summary>
        private async void PerformSignup()
        {
            if (string.IsNullOrWhiteSpace(Username) || string.IsNullOrWhiteSpace(Password))
            {
                ErrorMessage = "All fields must be filled.";
                return;
            }

            try
            {
                // Prepare the signup request and send it
                SignupRequest signupRequest = new SignupRequest
                {
                    Password = Password,
                    Username = Username,
                    Email = Email,
                    PhoneNumber = PhoneNumber,
                    HouseAddress = HouseAddress,
                    BirthDate = BirthDate,
                };

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
                    switch ((SignupResponseStatus)signupResponse.Status)
                    {
                        case SignupResponseStatus.Success:
                            // Navigate to the login page upon successful signup
                            MyNavigationService.Navigate(new LoginPage());
                            break;

                        case SignupResponseStatus.KnowenUsername:
                            ErrorMessage = "Known username.";
                            break;

                        case SignupResponseStatus.InvalidPassword:
                            ErrorMessage = $"Invalid password: {RegexFormats.Password}";
                            break;

                        case SignupResponseStatus.InvalidEmailFormat:
                            ErrorMessage = "Invalid email format.";
                            break;

                        case SignupResponseStatus.InvalidHousAddress:
                            ErrorMessage = $"Invalid address format. {RegexFormats.Email}";
                            break;

                        case SignupResponseStatus.InvalidPhoneNumber:
                            ErrorMessage = $"Invalid phone number. Expected format: {RegexFormats.PhoneNumber}";
                            break;

                        case SignupResponseStatus.InvalidBirthDate:
                            ErrorMessage = $"Invalid birth date format. Expected: {RegexFormats.Date}";
                            break;

                        default:
                            ErrorMessage = "An unknown error occurred.";
                            break;
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
