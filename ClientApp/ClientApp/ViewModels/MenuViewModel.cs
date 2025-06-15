using ClientApp.Commands;
using System.Windows.Input;
using ClientApp.Services;

namespace ClientApp.ViewModels
{
    /// <summary>
    /// ViewModel for the MenuPage in the client application. Handles user interactions with the menu options,
    /// such as creating a room, joining a room, viewing statistics, and logging out.
    /// </summary>
    internal class MenuViewModel : ViewModelBase
    {

        private readonly CountdownTimerViewModel _countdownTimerViewModel;
        public CountdownTimerViewModel Timer => _countdownTimerViewModel;

        /// <summary>
        /// Private constructor for the MenuPageViewModel. Initializes the commands for the actions available in the menu.
        /// </summary>
        public MenuViewModel(
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService)
        {
            NavToCreateRoomCmd = new NavigateCommand<CreateRoomViewModel>(navigationService);
            NavToJoinRoomCmd = new NavigateCommand<JoinRoomViewModel>(navigationService);
            NavToStatisticsCmd = new NavigateCommand<StatisticsViewModel>(navigationService);
            LogoutCmd = new LogoutCommand(this,
                navigationService,
                requestsExchangeService);

  
        }


        // Commands
        public ICommand NavToCreateRoomCmd { get; }
        public ICommand NavToJoinRoomCmd { get; }
        public ICommand NavToStatisticsCmd { get; }
        public ICommand LogoutCmd { get; }



        // Error messages fields
        private string _errorMessage;

        // Error message property
        public string ErrorMessage
        {
            get => _errorMessage;
            set { _errorMessage = value; OnPropertyChanged(); }
        }


    }
}
