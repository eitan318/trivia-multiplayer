using ClientApp.Commands;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Stores;
using ClientApp.ViewModels;

public class LoginCommand : CommandBase, IAsyncCommand
{
    private readonly INavigationService _navigationService;
    private readonly UserStore _userStore;
    private readonly RequestsExchangeService _requestsExchangeService;

    public LoginCommand(
        INavigationService navigationService,
        UserStore userStore,
        RequestsExchangeService requestsExchangeService)
    {
        _navigationService = navigationService;
        _userStore = userStore;
        _requestsExchangeService = requestsExchangeService;
    }

    public override bool CanExecute(object parameter)
    {
        if (parameter is LoginViewModel loginViewModel)
        {
            return !string.IsNullOrWhiteSpace(loginViewModel.Username) &&
                   !string.IsNullOrWhiteSpace(loginViewModel.Password);
        }
        return false;
    }

    public override async Task ExecuteAsync(object parameter)
    {
        if (parameter is LoginViewModel loginViewModel)
        {
            loginViewModel.ErrorMessage = "";
            loginViewModel.UsernameErrorMessage = "";
            loginViewModel.PasswordErrorMessage = "";

            try
            {
                string trimmedUsername = loginViewModel.Username?.Trim();
                string trimmedPassword = loginViewModel.Password?.Trim();
                _userStore.Username = trimmedUsername;

                var loginRequest = new LoginRequest(trimmedUsername, trimmedPassword);
                var responseInfo = await _requestsExchangeService.ExchangeRequest<LoginResponse>(loginRequest);

                if (responseInfo.NormalResponse)
                {
                    var loginResponse = responseInfo.Response;
                    if (loginResponse.Status == 0)
                    {
                        _navigationService.NavigateTo<MenuViewModel>();
                    }
                    else
                    {
                        loginViewModel.UsernameErrorMessage = loginResponse.Errors.UsernameError;
                        loginViewModel.PasswordErrorMessage = loginResponse.Errors.PasswordError;
                        loginViewModel.ErrorMessage = loginResponse.Errors.GeneralError;
                    }
                }
            }
            catch (Exception ex)
            {
                loginViewModel.ErrorMessage = $"Login failed: {ex.Message}";
            }
        }
    }
}
