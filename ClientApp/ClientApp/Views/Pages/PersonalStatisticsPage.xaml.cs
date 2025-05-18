using ClientApp.ViewModels;

using System.Windows.Controls;

namespace ClientApp.Views.Pages
{
    /// <summary>
    /// Interaction logic for PersonalStatisticsPage.xaml
    /// </summary>
    public partial class PersonalStatisticsPage : NavigablePage
    {
        public PersonalStatisticsPage(Page parent) : base(parent)
        {
            InitializeComponent();
            DataContext = PersonalStatisticsPageViewModel.Instance(this);
        }
    }
}
