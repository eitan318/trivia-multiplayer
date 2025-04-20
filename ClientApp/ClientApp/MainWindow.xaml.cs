using ClientApp.Views;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using System.Threading.Tasks;
using ClientApp.Services;
using ClientApp.Views.Pages;
using System.Windows.Interop;

namespace ClientApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Page initialPage;

        public MainWindow()
        {
            InitializeComponent();
            initialPage = new MenuPage();
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

        private void MainWindow_Closed(object sender, EventArgs e)
        {
            SocketService.CloseConnection();
        }



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
                    await Task.Delay(2000);
                }
            }
            MainFrame.Navigate(initialPage);
        }
    }
}
