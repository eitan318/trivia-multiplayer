using ClientApp.Commands;
using ClientApp.Services;
using ClientApp.Views.Controls;
using ClientApp.Views.Screens;
using System.Windows.Controls;
using System.Windows.Input;

namespace ClientApp.ViewModels
{
    /// <summary>
    /// ViewModel for the StatisticsPage in the client application. Handles user interactions for navigating
    /// to personal statistics and high scores pages.
    /// </summary>
    class StatisticsViewModel : ScreenViewModelBase
    {   
        /// <summary>
        /// Private constructor for the StatisticsPageViewModel. Initializes the commands for navigating to
        /// personal statistics and high scores pages.
        /// </summary>
        public StatisticsViewModel(INavigationService navigationService, TopBarViewModel topBarViewModel) : base(true)
        {
            TopBarVM = topBarViewModel;

            this.NavToPersonalStatisticsCmd = new NavigateCommand<PersonalStatisticsViewModel>(navigationService);
            this.NavToHighScoresCmd = new NavigateCommand<HighScoresViewModel>(navigationService);
        }

        public TopBarViewModel TopBarVM { get; }


        public ICommand NavToPersonalStatisticsCmd { get; }
        public ICommand NavToHighScoresCmd { get; }

    }
}
