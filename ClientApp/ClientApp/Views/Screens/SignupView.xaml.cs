using ClientApp.ViewModels;
using System.Windows.Controls;

namespace ClientApp.Views.Screens
{
    /// <summary>
    /// Interaction logic for SignupPage.xaml
    /// </summary>
    public partial class SignupView : UserControl
    {
        public SignupView()
        {
            InitializeComponent();
            // Use Loaded event to delay focus
            Loaded += (s, e) => UsernameTB.Focus();
        }

        private void PasswordBox_PasswordChanged(object sender, System.Windows.RoutedEventArgs e)
        {
            if (DataContext is SignupViewModel viewModel)
            {
                viewModel.Password = ((PasswordBox)sender).Password;
            }
        }
    }
}
