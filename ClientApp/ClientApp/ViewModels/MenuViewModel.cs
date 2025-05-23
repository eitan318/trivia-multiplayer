using ClientApp.Commands;
using System.Windows.Controls;
using System.Windows.Input;
using ClientApp.Views.Pages;
using ClientApp.Services;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Views;
using ClientApp.Stores;

namespace ClientApp.ViewModels
{
    /// <summary>
    /// ViewModel for the MenuPage in the client application. Handles user interactions with the menu options,
    /// such as creating a room, joining a room, viewing statistics, and logging out.
    /// </summary>
    internal class MenuViewModel : ViewModelBase
    {
        private INavigationService _navigationService;
        private readonly RequestsExchangeService _requestsExchangeService;

        /// <summary>
        /// Private constructor for the MenuPageViewModel. Initializes the commands for the actions available in the menu.
        /// </summary>
        public MenuViewModel(
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService)
        {
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService;
            NavToCreateRoomCmd = new NavigateCommand<CreateRoomViewModel>(navigationService);
            NavToJoinRoomCmd = new NavigateCommand<JoinRoomViewModel>(navigationService);
            NavToStatisticsCmd = new NavigateCommand<StatisticsViewModel>(navigationService);
            LogoutCmd = new RelayCommand(LogOut);
        }


        // Error messages fields
        private string _errorMessage;

        // Error message property
        public string ErrorMessage
        {
            get => _errorMessage;
            set { _errorMessage = value; OnPropertyChanged(); }
        }

        // Commands
        public ICommand NavToCreateRoomCmd { get; }
        public ICommand NavToJoinRoomCmd { get; }
        public ICommand NavToStatisticsCmd { get; }
        public ICommand LogoutCmd { get; }

        /// <summary>
        /// Logs the user out and navigates to the LoginPage if the logout is successful.
        /// </summary>
        private async void LogOut()
        {
            LogoutRequest request = new LogoutRequest();
            ResponseInfo<LogoutResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<LogoutResponse>(request);

            if (responseInfo.NormalResponse)
            {
                LogoutResponse logoutResponse = responseInfo.Response;

                if(logoutResponse.Status == 0)
                {
                    this._navigationService.NavigateTo<LoginViewModel>();
                }
                else
                {

                } 
            }
            else
            {
                ErrorMessage = responseInfo.ErrorResponse.Message;
            }
        }
    }
}
