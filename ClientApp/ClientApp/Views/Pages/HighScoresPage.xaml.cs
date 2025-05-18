using ClientApp.ViewModels;
using System.Windows.Controls;

namespace ClientApp.Views.Pages
{
    /// <summary>
    /// Interaction logic for HighScoresPage.xaml
    /// </summary>
    public partial class HighScoresPage : NavigablePage
    {
        public HighScoresPage(Page parent) : base(parent)
        {
            InitializeComponent();
            DataContext = HighScoresPageViewModel.Instance();

        }
    }
}
