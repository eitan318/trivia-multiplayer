using System.Windows.Controls;
using ClientApp.ViewModels;

namespace ClientApp.Views.Screens
{
    /// <summary>
    /// Interaction logic for LoginPage.xaml
    /// </summary>
    public partial class LoginView : UserControl
    {
        public LoginView()
        {
            InitializeComponent();
            
            // Use Loaded event to delay focus
            Loaded += (s, e) => UsernameTB.Focus();
        }

    }
}
