using ClientApp.Commands;
using ClientApp.Services;
using ClientApp.Views.Screens;
using System.Windows.Controls;
using System.Windows.Input;

namespace ClientApp.ViewModels
{
    /// <summary>
    /// ViewModel for the StatisticsPage in the client application. Handles user interactions for navigating
    /// to personal statistics and high scores pages.
    /// </summary>
    class StatisticsViewModel : ViewModelBase
    {   
        /// <summary>
        /// Private constructor for the StatisticsPageViewModel. Initializes the commands for navigating to
        /// personal statistics and high scores pages.
        /// </summary>
        public StatisticsViewModel(INavigationService navigationService) : base(true)
        {
            this.NavToPersonalStatisticsCmd = new NavigateCommand<PersonalStatisticsViewModel>(navigationService);
            this.NavToHighScoresCmd = new NavigateCommand<HighScoresViewModel>(navigationService);
        }


        public ICommand NavToPersonalStatisticsCmd { get; }
        public ICommand NavToHighScoresCmd { get; }

    }
}
