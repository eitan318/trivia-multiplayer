using ClientApp.ViewModels;
using System.Windows.Controls;

namespace ClientApp.Views.Pages
{
    public partial class StatisticsPage : NavigablePage
    {
        public StatisticsPage(Page parent) : base(parent)
        {
            InitializeComponent();
            DataContext = StatisticsPageViewModel.Instance(this);
        }
    }
}
