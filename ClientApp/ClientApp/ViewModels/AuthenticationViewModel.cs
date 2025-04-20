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
            set => SetProperty(ref _password, value);
        }

        public string Username
        {
            get => _username;
            set => SetProperty(ref _username, value);
        }

        public string Email
        {
            get => _email;
            set => SetProperty(ref _email, value);
        }


        public string PhoneNumber
        {
            get => _phoneNumber;
            set => SetProperty(ref _phoneNumber, value);
        }

        public string HouseAddress
        {
            get => _houseAddress;
            set => SetProperty(ref _houseAddress, value);
        }

        public string BirthDate
        {
            get => _birthDate;
            set => SetProperty(ref _birthDate, value);
        }


        private string _errorMessage;
        public string ErrorMessage
        {
            get => _errorMessage;
            set => SetProperty(ref _errorMessage, value);
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
            if (string.IsNullOrWhiteSpace(Username) || string.IsNullOrWhiteSpace(Password))
            {
                ErrorMessage = "Username and Password cannot be empty.";
                return;
            }

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
                    string[] errMsg = {
                        "",
                         "username does not exist",
                         "password doesnt match username"
                    };


                    ErrorMessage = errMsg[loginResponse.Status];

                    if (loginResponse.Status == 0)
                    {
                        MyNavigationService.Navigate(new MenuPage());
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
