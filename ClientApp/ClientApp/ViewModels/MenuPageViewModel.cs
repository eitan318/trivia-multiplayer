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

namespace ClientApp.ViewModels
{
    public class MenuPageViewModel : BaseViewModel
    {
        public Page ownerPage;
        private MenuPageViewModel(Page owner)
        {
            this.ownerPage = owner;
            CreateRoomCommand = new RelayCommand(CreateRoom);
            JoinRoomCommand = new RelayCommand(JoinRoom);
            ShowStatisticsCommand = new RelayCommand(ShowStatistics);
            LogoutCommand = new RelayCommand(LogOut);
        }
        public static MenuPageViewModel Instance(Page owner)
        {
            return GetInstance(() => new MenuPageViewModel(owner));
        }




        public ICommand CreateRoomCommand { get; }
        public ICommand JoinRoomCommand { get; }
        public ICommand ShowStatisticsCommand { get; }
        public ICommand LogoutCommand { get; }

        private void CreateRoom()
        {
            MyNavigationService.Navigate(new CreateRoomPage(ownerPage));
        }

        private void JoinRoom()
        {
            MyNavigationService.Navigate(new JoinRoomPage(ownerPage));
        }

        private void ShowStatistics()
        {
            MyNavigationService.Navigate(new StatisticsPage(ownerPage));
        }

        private async void LogOut() 
        {

            LogoutRequest request = new LogoutRequest();
            ResponseInfo responseInfo = await RequestsExchangeService.ExchangeRequest(request);
            if(responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
            {
                ErrorResponse errorResponse = JsonResponseDeserialize.DeserializeResponse<ErrorResponse>(responseInfo);
            }
            else
            {
                NoDataResponse logoutResponse = JsonResponseDeserialize.DeserializeResponse<NoDataResponse>(responseInfo);
                if (logoutResponse.Status == 0)
                {
                    MyNavigationService.Navigate(new LoginPage());
                }
                else
                {

                }

            }

        }
    }
}
