using ClientApp.Views;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using System.Threading.Tasks;
using ClientApp.Services;
using ClientApp.Views.Pages;
using System.Windows.Interop;
using ClientApp.Models.Responses;

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
            InitializeComponent();
            initialPage = new LoginPage();
            SocketService.Initialize("127.0.0.1", 5554);
            MyNavigationService.Initialize(MainFrame);

            try
            {
                SocketService.Connect();
                MainFrame.Navigate(initialPage);
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
