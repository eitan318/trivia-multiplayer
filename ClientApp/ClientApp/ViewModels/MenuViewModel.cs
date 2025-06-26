using ClientApp.Commands;
using System.Windows.Input;
using ClientApp.Services;
using ClientApp.Stores;

namespace ClientApp.ViewModels
{
    /// <summary>
    /// ViewModel for the MenuPage in the client application. Handles user interactions with the menu options,
    /// such as creating a room, joining a room, viewing statistics, and logging out.
    /// </summary>
    internal class MenuViewModel : ScreenViewModelBase
    {

        /// <summary>
        /// Private constructor for the MenuPageViewModel. Initializes the commands for the actions available in the menu.
        /// </summary>
        public MenuViewModel(
            TopBarViewModel topBarViewModel,
            NavigateCommand<CreateRoomViewModel> navToCreateRoomCommand,
            NavigateCommand<JoinRoomViewModel> navToJoinRoomCommand,
            Join1v1WaitingListCommand join1v1WaitingListCommand,
            NavigateCommand<StatisticsViewModel> navToStatisticsCommand
            ) : base(false, topBarViewModel)
        {
            NavToCreateRoomCmd = navToCreateRoomCommand;
            NavToJoinRoomCmd = navToJoinRoomCommand;
            NavToStatisticsCmd = navToStatisticsCommand;
            Join1v1WaitingCmd = join1v1WaitingListCommand;
        }


        // Commands
        public ICommand NavToCreateRoomCmd { get; }
        public ICommand NavToJoinRoomCmd { get; }
        public ICommand NavToStatisticsCmd { get; }
        public ICommand Join1v1WaitingCmd { get; }



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
