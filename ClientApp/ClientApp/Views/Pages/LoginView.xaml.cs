using System.Windows.Controls;
using ClientApp.ViewModels;

namespace ClientApp.Views.Pages
{
    /// <summary>
    /// Interaction logic for LoginPage.xaml
    /// </summary>
    public partial class LoginView : Page
    {
        public LoginView()
        {
            InitializeComponent();
            UsernameTB.Focus();
        }

    }
}
