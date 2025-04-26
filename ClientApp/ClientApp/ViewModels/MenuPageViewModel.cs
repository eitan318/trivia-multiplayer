using ClientApp.Commands;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Navigation;
using ClientApp.Views.Pages;
using ClientApp.Services;
using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Views;
using ClientApp.ViewModels.ClientApp.ViewModels;
using ClientApp.Enums;

namespace ClientApp.ViewModels
{
    /// <summary>
    /// ViewModel for the MenuPage in the client application. Handles user interactions with the menu options,
    /// such as creating a room, joining a room, viewing statistics, and logging out.
    /// </summary>
    public class MenuPageViewModel : BaseViewModel
    {
        /// <summary>
        /// The page that owns this ViewModel. Used for navigation purposes.
        /// </summary>
        public Page ownerPage;

        /// <summary>
        /// Private constructor for the MenuPageViewModel. Initializes the commands for the actions available in the menu.
        /// </summary>
        /// <param name="owner">The page that owns this ViewModel.</param>
        private MenuPageViewModel(Page owner)
        {
            this.ownerPage = owner;
            CreateRoomCommand = new RelayCommand(CreateRoom);
            JoinRoomCommand = new RelayCommand(JoinRoom);
            ShowStatisticsCommand = new RelayCommand(ShowStatistics);
            LogoutCommand = new RelayCommand(LogOut);
        }

        /// <summary>
        /// Gets the singleton instance of the MenuPageViewModel.
        /// </summary>
        /// <param name="owner">The page that owns this ViewModel.</param>
        /// <returns>The singleton instance of MenuPageViewModel.</returns>
        public static MenuPageViewModel Instance(Page owner)
        {
            return GetInstance(() => new MenuPageViewModel(owner));
        }

        /// <summary>
        /// Command to create a new room.
        /// </summary>
        public ICommand CreateRoomCommand { get; }

        /// <summary>
        /// Command to join an existing room.
        /// </summary>
        public ICommand JoinRoomCommand { get; }

        /// <summary>
        /// Command to show the statistics page.
        /// </summary>
        public ICommand ShowStatisticsCommand { get; }

        /// <summary>
        /// Command to log the user out.
        /// </summary>
        public ICommand LogoutCommand { get; }

        /// <summary>
        /// Navigates to the CreateRoomPage when the user chooses to create a new room.
        /// </summary>
        private void CreateRoom()
        {
            MyNavigationService.Navigate(new CreateRoomPage(ownerPage));
        }

        /// <summary>
        /// Navigates to the JoinRoomPage when the user chooses to join an existing room.
        /// </summary>
        private void JoinRoom()
        {
            MyNavigationService.Navigate(new JoinRoomPage(ownerPage));
        }

        /// <summary>
        /// Navigates to the StatisticsPage when the user chooses to view the statistics.
        /// </summary>
        private void ShowStatistics()
        {
            MyNavigationService.Navigate(new StatisticsPage(ownerPage));
        }

        /// <summary>
        /// Logs the user out and navigates to the LoginPage if the logout is successful.
        /// </summary>
        private async void LogOut()
        {
            LogoutRequest request = new LogoutRequest();
            ResponseInfo responseInfo = await RequestsExchangeService.ExchangeRequest(request);

            if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
            {
                ErrorResponse errorResponse = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
            }
            else
            {
                LogoutResponse logoutResponse = JsonResponseDeserialize.DeserializeResponse<LogoutResponse>(responseInfo);

                switch (logoutResponse.Status)
                {
                    case (byte)LogoutResponseStatus.Success:
                        MyNavigationService.Navigate(new LoginPage());
                        break;
                }
            }
        }
    }
}
