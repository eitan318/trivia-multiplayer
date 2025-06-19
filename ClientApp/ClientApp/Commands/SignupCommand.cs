using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.ViewModels;
using ClientApp.Commands;
using ClientApp.Services;
using ClientApp.Stores;

namespace ClientApp.Commands
{
    class SignupCommand : CommandBase 
    {
        private readonly INavigationService _navigationService;
        private SignupViewModel _signupViewModel;
        private readonly RequestsExchangeService _requestsExchangeService;

        public SignupCommand(
            SignupViewModel signupViewModel,
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService)
        {
            this._signupViewModel = signupViewModel;
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService; 

        }

        /// <summary>
        /// Attempts to sign up the user by validating the input fields and sending the signup request.
        /// If the signup is successful, navigates to the login page. If there are errors, displays error messages.
        /// </summary>
        public override async void Execute(object parameter)
        {
            const string cannotBeEmptyString = "Cannot be empty";

            // Reset error messages
            _signupViewModel.ErrorMessage = "";
            _signupViewModel.UsernameErrorMessage = "";
            _signupViewModel.PasswordErrorMessage = "";
            _signupViewModel.EmailErrorMessage = "";
            _signupViewModel.PhoneNumberErrorMessage = "";
            _signupViewModel.HouseAddressErrorMessage = "";
            _signupViewModel.BirthDateErrorMessage = "";

            bool requiredNotEmpty = true;

            // Trim input values
            string trimmedUsername = _signupViewModel.Username?.Trim();
            string trimmedPassword = _signupViewModel.Password?.Trim();
            string trimmedEmail = _signupViewModel.Email?.Trim();
            string trimmedPhoneNumber = _signupViewModel.PhoneNumber?.Trim();
            string trimmedHouseAddress = _signupViewModel.HouseAddress?.Trim();
            string trimmedBirthDate = _signupViewModel.BirthDate?.ToString("dd/MM/yyyy")??"";


            // Validate each field
            if (string.IsNullOrWhiteSpace(_signupViewModel.Username))
            {
                _signupViewModel.UsernameErrorMessage = cannotBeEmptyString;
                requiredNotEmpty = false;
            }

            if (string.IsNullOrWhiteSpace(_signupViewModel.Password))
            {
                _signupViewModel.PasswordErrorMessage = cannotBeEmptyString;
                requiredNotEmpty = false;
            }

            if (string.IsNullOrWhiteSpace(_signupViewModel.Email))
            {
                _signupViewModel.EmailErrorMessage = cannotBeEmptyString;
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

                ResponseInfo<SignupResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<SignupResponse>(signupRequest);

                // Handle server error response
                if (responseInfo.NormalResponse)
                {
                    SignupResponse signupResponse = responseInfo.Response;
                    if(signupResponse.Status == 0 && requiredNotEmpty)
                    {
                        // Navigate to the login page upon successful signup
                        this._navigationService.NavigateTo<LoginViewModel>();
                    }
                    else
                    {
                        if(_signupViewModel.UsernameErrorMessage == "")
                            _signupViewModel.UsernameErrorMessage = signupResponse.Errors.UsernameError;
                        if (_signupViewModel.PasswordErrorMessage == "") 
                            _signupViewModel.PasswordErrorMessage = signupResponse.Errors.PasswordError;
                        if (_signupViewModel.EmailErrorMessage == "")
                            _signupViewModel.EmailErrorMessage = signupResponse.Errors.EmailError;
                        _signupViewModel.HouseAddressErrorMessage = signupResponse.Errors.HouseAddressError;
                        _signupViewModel.PhoneNumberErrorMessage = signupResponse.Errors.PhoneNumberError;
                        _signupViewModel.BirthDateErrorMessage = signupResponse.Errors.BirthDateError;
                    } 
                }
            }
            catch (Exception ex)
            {
                _signupViewModel.ErrorMessage = $"Signup failed (sent from client side): {ex.Message}";
            }
        }
    }
}
