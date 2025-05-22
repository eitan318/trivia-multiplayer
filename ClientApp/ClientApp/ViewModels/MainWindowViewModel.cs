using ClientApp.Services;
using ClientApp.Views.Pages;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.ViewModels
{
    class MainWindowViewModel : ViewModelBase
    {
        INavigationService _navigationService;
        public MainWindowViewModel(INavigationService navigationService) { 
            this._navigationService = navigationService;
            
            SocketService.Initialize("127.0.0.1", 5554);

            try
            {
                SocketService.Connect();
                _navigationService.NavigateTo<LoginViewModel>();
            }
            catch (Exception ex)
            {
                AttemptConnectionAsync();
            }
        }

        /// <summary>
        /// Attempts to establish a connection to the server. If the connection fails, 
        /// retries the connection every 2 seconds until successful.
        /// Displays an error page while attempting to connect.
        /// </summary>
        private async void AttemptConnectionAsync()
        {
            // Display the error page
            var errorPage = new ErrorPage("Connection Error", "Unable to connect to Server. Trying...");
            _navigationService.NavigateTo<ErrorViewModel>();

            while (true)
            {
                try
                {
                    await Task.Run(() => SocketService.Connect());
                    break;
                }
                catch
                {
                    await Task.Delay(2000); // Wait for 2 seconds before retrying
                }
            }

            _navigationService.NavigateTo<LoginViewModel>();
        }
    }



}
