using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.ViewModels;
using ClientApp.Commands;
using ClientApp.Services;
using ClientApp.Stores;

namespace ClientApp.Commands
{
    class SignupCommand : CommandBase , IAsyncCommand
    {
        private readonly INavigationService _navigationService;
        private readonly RequestsExchangeService _requestsExchangeService;

        public SignupCommand(
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService)
        {
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService; 

        }

        /// <summary>
        /// Attempts to sign up the user by validating the input fields and sending the signup request.
        /// If the signup is successful, navigates to the login page. If there are errors, displays error messages.
        /// </summary>
        public override async Task ExecuteAsync(object parameter)
        {
            if (parameter is not SignupViewModel signupViewModel)
            {
                return;
            }

            const string cannotBeEmptyString = "Cannot be empty";

            // Reset error messages
            signupViewModel.ErrorMessage = "";
            signupViewModel.UsernameErrorMessage = "";
            signupViewModel.PasswordErrorMessage = "";
            signupViewModel.EmailErrorMessage = "";
            signupViewModel.PhoneNumberErrorMessage = "";
            signupViewModel.HouseAddressErrorMessage = "";
            signupViewModel.BirthDateErrorMessage = "";

            bool requiredNotEmpty = true;

            // Trim input values
            string trimmedUsername = signupViewModel.Username?.Trim();
            string trimmedPassword = signupViewModel.Password?.Trim();
            string trimmedEmail = signupViewModel.Email?.Trim();
            string trimmedPhoneNumber = signupViewModel.PhoneNumber?.Trim();
            string trimmedHouseAddress = signupViewModel.HouseAddress?.Trim();
            string trimmedBirthDate = signupViewModel.BirthDate?.ToString("dd/MM/yyyy")??"";


            // Validate each field
            if (string.IsNullOrWhiteSpace(signupViewModel.Username))
            {
                signupViewModel.UsernameErrorMessage = cannotBeEmptyString;
                requiredNotEmpty = false;
            }

            if (string.IsNullOrWhiteSpace(signupViewModel.Password))
            {
                signupViewModel.PasswordErrorMessage = cannotBeEmptyString;
                requiredNotEmpty = false;
            }

            if (string.IsNullOrWhiteSpace(signupViewModel.Email))
            {
                signupViewModel.EmailErrorMessage = cannotBeEmptyString;
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
                        if(signupViewModel.UsernameErrorMessage == "")
                            signupViewModel.UsernameErrorMessage = signupResponse.Errors.UsernameError;
                        if (signupViewModel.PasswordErrorMessage == "") 
                            signupViewModel.PasswordErrorMessage = signupResponse.Errors.PasswordError;
                        if (signupViewModel.EmailErrorMessage == "")
                            signupViewModel.EmailErrorMessage = signupResponse.Errors.EmailError;
                        signupViewModel.HouseAddressErrorMessage = signupResponse.Errors.HouseAddressError;
                        signupViewModel.PhoneNumberErrorMessage = signupResponse.Errors.PhoneNumberError;
                        signupViewModel.BirthDateErrorMessage = signupResponse.Errors.BirthDateError;
                    } 
                }
            }
            catch (Exception ex)
            {
                signupViewModel.ErrorMessage = $"Signup failed (sent from client side): {ex.Message}";
            }
        }
    }
}
