using ClientApp.ViewModels;
using System.Windows.Controls;

namespace ClientApp.Views.Pages
{
    /// <summary>
    /// Interaction logic for MenuPage.xaml
    /// </summary>
    public partial class MenuPage : Page
    {
        public MenuPage(string user)
        {
            InitializeComponent();
            DataContext = MenuPageViewModel.Instance(this, user);
        }
    }

}
