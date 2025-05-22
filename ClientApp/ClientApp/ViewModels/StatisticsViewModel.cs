using ClientApp.Commands;
using ClientApp.Services;
using ClientApp.Views.Pages;
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
        private StatisticsViewModel(INavigationService navigationService)
        {
            this.NavToPersonalStatisticsCmd = new NavigateCommand<PersonalStatisticsViewModel>(navigationService);
            this.NavToHighScoresCmd = new NavigateCommand<HighScoresViewModel>(navigationService);
        }

        /// <summary>
        /// Gets the singleton instance of the StatisticsPageViewModel.
        /// </summary>
        /// <returns>The singleton instance of StatisticsPageViewModel.</returns>
        public static StatisticsViewModel Instance(INavigationService navigationService)
        {
            return GetInstance(() => new StatisticsViewModel(navigationService));
        }


        public ICommand NavToPersonalStatisticsCmd { get; }
        public ICommand NavToHighScoresCmd { get; }

    }
}
