using System.Windows.Controls;
using ClientApp.ViewModels;

namespace ClientApp.Views
{
    /// <summary>
    /// Interaction logic for LoginPage.xaml
    /// </summary>
    public partial class LoginPage : Page
    {
        public LoginPage()
        {
            InitializeComponent();
            DataContext = AuthenticationViewModel.Instance();
            UsernameTB.Focus();
        }

    }
}
