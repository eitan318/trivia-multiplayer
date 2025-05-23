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

        /// <summary>
        /// Initializes a new instance of the <see cref="MainWindow"/> class.
        /// Sets up the initial page, initializes socket connection, and navigation service.
        /// </summary>
        public MainWindow()
        {
            InitializeComponent();

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




    }
}
