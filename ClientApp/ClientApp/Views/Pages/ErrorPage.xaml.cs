using ClientApp.ViewModels.ClientApp.ViewModels;
using System.Windows.Controls;

namespace ClientApp.Views.Pages
{
    /// <summary>
    /// Interaction logic for ErrorPage.xaml
    /// </summary>
    public partial class ErrorPage : Page
    {
        public ErrorPage(string title, string initialMessage)
        {
            InitializeComponent();
            DataContext = ErrorPageViewModel.Instance(initialMessage);  
        }
    }
}
