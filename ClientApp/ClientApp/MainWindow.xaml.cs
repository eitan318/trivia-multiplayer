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
        public MainWindow(MainWindowViewModel viewModel)
        {
            DataContext = viewModel; // Set the DataContext to the provided ViewModel
            InitializeComponent();
            Closed += (sender, e) => viewModel.OnWindowClosed();
        }

    }
}
