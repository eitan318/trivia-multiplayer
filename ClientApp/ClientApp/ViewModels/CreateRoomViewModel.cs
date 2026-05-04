using System.Windows.Input;
using ClientApp.Commands;
using ClientApp.Models;
using ClientApp.Services;
using ClientApp.Stores;

namespace ClientApp.ViewModels
{
    /// <summary>
    /// ViewModel for the Create Room page, managing the room creation process and player data.
    /// </summary>
    class CreateRoomViewModel : ScreenViewModelBase
    {
        private readonly RoomDataStore _roomDataStore;

        /// <summary>
        /// Constructor for initializing the ViewModel.
        /// </summary>
        public CreateRoomViewModel(
            RoomDataStore roomDataStore,
            TopBarViewModel topBarViewModel,
            CreateRoomCommand createRoomCommand) : base(true)
        {
            _roomDataStore = roomDataStore;
            _roomDataStore.CurrentRoomData = new RoomDataModel();


            // Set default values
            CurrentRoomData.TimePerQuestion = 10;
            CurrentRoomData.MaxPlayers = 2;
            CurrentRoomData.NumOfQuestionsInGame = 3;
            CurrentRoomData.ScoreShowingTime = 3;

            CreateRoomCmd = createRoomCommand;

            CurrentRoomData.PropertyChanged += (_, args) =>
            {
                if (args.PropertyName == nameof(RoomDataModel.RoomName) ||
                    args.PropertyName == nameof(RoomDataModel.MaxPlayers) ||
                    args.PropertyName == nameof(RoomDataModel.NumOfQuestionsInGame) ||
                    args.PropertyName == nameof(RoomDataModel.TimePerQuestion) ||
                    args.PropertyName == nameof(RoomDataModel.ScoreShowingTime))
                {
                    ((CommandBase)CreateRoomCmd).RaiseCanExecuteChanged();
                }
            };
        }

        /// <summary>
        /// Direct access to the current room data.
        /// </summary>
        public RoomDataModel CurrentRoomData => _roomDataStore.CurrentRoomData;

        // Commands
        public ICommand CreateRoomCmd { get; }

        // Error message fields
        private string _questionCountError;


        /// <summary>
        /// Error message related to the number of questions.
        /// </summary>
        public string QuestionCountError
        {
            get => _questionCountError;
            set 
            {
                _questionCountError = value; 
                OnPropertyChanged();
            }
        }




        
    }
}
