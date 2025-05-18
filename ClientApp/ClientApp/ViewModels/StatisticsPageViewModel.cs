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
    class StatisticsPageViewModel : BaseViewModel
    {
        /// <summary>
        /// The page that owns this ViewModel. Used for navigation purposes.
        /// </summary>
        private Page ownerPage;

        /// <summary>
        /// Private constructor for the StatisticsPageViewModel. Initializes the commands for navigating to
        /// personal statistics and high scores pages.
        /// </summary>
        /// <param name="owner">The page that owns this ViewModel.</param>
        private StatisticsPageViewModel(Page owner)
        {
            this.ownerPage = owner;
            this.NavigateToPersonalStatisticsCommand = new RelayCommand(NavigateToPersonalStatistics);
            this.NavigateToHighScoresCommand = new RelayCommand(NavigateToHighScores);
        }

        /// <summary>
        /// Gets the singleton instance of the StatisticsPageViewModel.
        /// </summary>
        /// <param name="owner">The page that owns this ViewModel.</param>
        /// <returns>The singleton instance of StatisticsPageViewModel.</returns>
        public static StatisticsPageViewModel Instance(Page owner)
        {
            return GetInstance(() => new StatisticsPageViewModel(owner));
        }


        public ICommand NavigateToPersonalStatisticsCommand { get; }
        public ICommand NavigateToHighScoresCommand { get; }

        /// <summary>
        /// Navigates to the HighScoresPage when the user chooses to view the high scores.
        /// </summary>
        public void NavigateToHighScores()
        {
            MyNavigationService.Navigate(new HighScoresPage(this.ownerPage));
        }

        /// <summary>
        /// Navigates to the PersonalStatisticsPage when the user chooses to view their personal statistics.
        /// </summary>
        public void NavigateToPersonalStatistics()
        {
            MyNavigationService.Navigate(new PersonalStatisticsPage(this.ownerPage));
        }
    }
}
