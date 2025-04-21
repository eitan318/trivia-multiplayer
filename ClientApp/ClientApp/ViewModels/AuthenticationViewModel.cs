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
    class AuthenticationViewModel : BaseViewModel
    {
        private AuthenticationViewModel()
        {
            SignupCommand = new RelayCommand(PerformSignup);
            NavigateToLoginCommand = new RelayCommand(NavigateToLogin);
            LoginCommand = new RelayCommand(PerformLogin);
            NavigateToSignupCommand = new RelayCommand(NavigateToSignup);
            NavigateToForgotPasswordCommand = new RelayCommand(NavigateToForgotPassword);
        }
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
        public string Password
        {
            get => _password;
            set { _password = value; OnPropertyChanged(); }
        }

        public string Username
        {
            get => _username;
            set { _username = value; OnPropertyChanged(); }
        }

        public string Email
        {
            get => _email;
            set { _email = value; OnPropertyChanged(); }
        }


        public string PhoneNumber
        {
            get => _phoneNumber;
            set { _phoneNumber = value; OnPropertyChanged(); }
        }

        public string HouseAddress
        {
            get => _houseAddress;
            set { _houseAddress = value; OnPropertyChanged(); }
        }

        public string BirthDate
        {
            get => _birthDate;
            set { _birthDate = value; OnPropertyChanged(); }
        }


        private string _passwordErrorMessage;
        public string PasswordErrorMessage
        {
            get => _passwordErrorMessage;
            set { _passwordErrorMessage = value; OnPropertyChanged(); }
        }

        private string _usernameErrorMessage;
        public string UsernameErrorMessage
        {
            get => _usernameErrorMessage;
            set { _usernameErrorMessage = value; OnPropertyChanged(); }
        }



        private string _errorMessage;
        public string ErrorMessage
        {
            get => _errorMessage;
            set { _errorMessage = value; OnPropertyChanged(); }
        }

        public ICommand SignupCommand { get; }
        public ICommand LoginCommand { get; }
        public ICommand NavigateToForgotPasswordCommand { get; }
        public ICommand NavigateToLoginCommand { get; }
        public ICommand NavigateToSignupCommand { get; }



        private void NavigateToSignup()
        {
            MyNavigationService.Navigate(new SignupPage());
        }

        private void NavigateToForgotPassword()
        {
            MyNavigationService.Navigate(new ForgotPasswordPage(new LoginPage()));
        }

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
                LoginRequest loginRequest = new LoginRequest
                {
                    Password = Password,
                    Username = Username,
                };

                ResponseInfo responseInfo = await RequestsExchangeService.ExchangeRequest(loginRequest);
                if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
                {
                    ErrorResponse errorResponse = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
                    ErrorMessage = "SERVER ERROR: " + errorResponse.Message;
                }
                else
                {
                    NoDataResponse loginResponse = JsonResponseDeserialize.DeserializeResponse<NoDataResponse>(responseInfo);
                    switch (loginResponse.Status)
                    {
                        case (byte)LoginResponseStatus.Success:
                            MyNavigationService.Navigate(new MenuPage());
                            break;
                        case (byte)LoginResponseStatus.UnknowenUsername:
                            UsernameErrorMessage = "username does not exist";
                            break;
                        case (byte)LoginResponseStatus.PasswordDoesntMatch:
                            PasswordErrorMessage = "password doesnt match username";
                            break;

                    }

                }
            }
            catch (Exception ex)
            {
                ErrorMessage = $"Login failed(sent from client side): {ex.Message}";
            }
        }



        private void NavigateToLogin()
        {
            MyNavigationService.Navigate(new LoginPage());
        }

        private async void PerformSignup()
        {
            if (string.IsNullOrWhiteSpace(Username) || string.IsNullOrWhiteSpace(Password))
            {
                ErrorMessage = "All fields must be filled.";
                return;
            }

            try
            {
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

                if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
                {
                    ErrorResponse errorResponse = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
                    ErrorMessage = "SERVER ERROR: " + errorResponse.Message;
                }
                else
                {
                    NoDataResponse signupResponse = JsonResponseDeserialize.DeserializeResponse<NoDataResponse>(responseInfo);

                    string[] errMsg = {
                        "",
                        "Known username.",
                        "Invalid password: " + RegexFormats.Password,
                        "Invalid email format.",
                        "Invalid address format. " + RegexFormats.Email,
                        "Invalid phone number. Expected format: " + RegexFormats.PhoneNumber,
                        "Invalid birth date format. Expected: " + RegexFormats.Date,
                    };

                    ErrorMessage = errMsg[signupResponse.Status];

                    if (signupResponse.Status == 0)
                    {
                        MyNavigationService.Navigate(new LoginPage());
                    }
                }


                    
            }
            catch (Exception ex)
            {
                ErrorMessage = $"Signup failed(sent from client side): {ex.Message}";
            }
        }

    }
}
