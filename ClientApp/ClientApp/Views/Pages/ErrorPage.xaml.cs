using System.Windows.Controls;
using ClientApp.ViewModels;

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
            DataContext = ErrorViewModel.Instance(initialMessage);  
        }
    }
}
