using ClientApp.Commands;
using ClientApp.Services;
using ClientApp.ViewModels.ClientApp.ViewModels;
using ClientApp.Views.Pages;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Input;

namespace ClientApp.ViewModels
{
    class StatisticsPageViewModel : BaseViewModel
    {
        private StatisticsPageViewModel(Page owner)
        {
            this.ownerPage = owner;
            this.NavigateToPersonalStatisticsCommand = new RelayCommand(NavigateToPersonalStatistics);
            this.NavigateToHighScoresCommand = new RelayCommand(NavigateToHighScores);
        }
        public static StatisticsPageViewModel Instance(Page owner)
        {
            return GetInstance(() => new StatisticsPageViewModel(owner));
        }

        private Page ownerPage;

        public ICommand NavigateToPersonalStatisticsCommand { get; }
        public ICommand NavigateToHighScoresCommand { get; }


        public void NavigateToHighScores()
        {
            MyNavigationService.Navigate(new HighScoresPage(this.ownerPage));
        }

        public void NavigateToPersonalStatistics()
        {
            MyNavigationService.Navigate(new PersonalStatisticsPage(this.ownerPage));
        }




    }
}
