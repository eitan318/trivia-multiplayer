using ClientApp.ViewModels;
using System.Windows.Controls;

namespace ClientApp.Views.Pages
{
    public partial class StatisticsPage : CustomPage
    {
        public StatisticsPage() 
        {
            InitializeComponent();
            DataContext = StatisticsViewModel.Instance();
        }
    }
}
