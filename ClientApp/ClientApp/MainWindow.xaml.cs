using ClientApp.Views;
using System.Windows;
using System.Windows.Controls;
using ClientApp.Services;
using ClientApp.Views.Pages;
using ClientApp.ViewModels;

namespace ClientApp
{
    /// <summary>
    /// Interaction logic for the main window of the application.
    /// </summary>
    public partial class MainWindow : Window
    {
        private Page initialPage;

        /// <summary>
        /// Initializes a new instance of the <see cref="MainWindow"/> class.
        /// Sets up the initial page, initializes socket connection, and navigation service.
        /// </summary>
        public MainWindow()
        {
            MainWindowViewModel mainViewModel = new MainWindowViewModel();
            InitializeComponent();
            DataContext = new MainWindowViewModel();
            initialPage = new LoginPage();
            SocketService.Initialize("127.0.0.1", 5554);

            try
            {
                SocketService.Connect();
                mainViewModel.NavigateToLoginPage();
            }
            catch (Exception ex)
            {
                AttemptConnectionAsync();
            }
            this.Closed += MainWindow_Closed; // Subscribe to the Closed event
        }

        /// <summary>
        /// Handles the event when the window is closed. 
        /// Ensures that the socket connection is properly closed when the window is closed.
        /// </summary>
        private void MainWindow_Closed(object sender, EventArgs e)
        {
            SocketService.CloseConnection();
        }


        private void MainFrame_ContentRendered(object sender, EventArgs e)
        {
            var currentPage = MainFrame.Content as CustomPage;
            BackButton.Visibility = currentPage?.ShowBackButton == true
                ? Visibility.Visible
                : Visibility.Collapsed;
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            if (MainFrame.CanGoBack)
            {
                MainFrame.GoBack();
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
            MainFrame.Navigate(errorPage);

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
            MainFrame.Navigate(initialPage); // Navigate to the initial page once connected
        }
    }
}
