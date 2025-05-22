using ClientApp.ViewModels;
using System.Windows.Controls;

namespace ClientApp.Views.Pages
{
    /// <summary>
    /// Interaction logic for HighScoresPage.xaml
    /// </summary>
    public partial class HighScoresPage : CustomPage
    {
        public HighScoresPage() 
        {
            InitializeComponent();
            DataContext = HighScoresViewModel.Instance();

        }
    }
}
