using System.Windows.Input;
using ClientApp.Commands;
using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Views.Screens;
using ClientApp.Stores;

namespace ClientApp.ViewModels
{
    /// <summary>
    /// ViewModel for the Create Room page, managing the room creation process and player data.
    /// </summary>
    class CreateRoomViewModel : ViewModelBase
    {
        
        /// <summary>
        /// Private constructor for initializing the ViewModel.
        /// </summary>
        public CreateRoomViewModel(
            RequestsExchangeService requestsExchangeService,
            INavigationService navigationService,
            RoomDataStore roomDataStore) : base(true)
        {
            CreateRoomCmd = new CreateRoomCommand(this, 
                requestsExchangeService,
                navigationService,
                roomDataStore);

            PropertyChanged += (sender, args) =>
            {
                if (args.PropertyName == nameof(RoomName) ||
                    args.PropertyName == nameof(MaxPlayers) ||
                    args.PropertyName == nameof(QuestionsCount) ||
                    args.PropertyName == nameof(QuestionTimeout))
                {
                    ((BaseCommand)CreateRoomCmd).RaiseCanExecuteChanged();
                }
            };

        }

        // Commands
        public ICommand CreateRoomCmd { get; }


        // Room fields
        private string _roomName;
        private double _questionTimeout = 1; //Min val from xaml
        private uint _maxPlayers = 1; //Min val from xaml
        private uint _questionsCount = 1; //Min val from xaml

        // Error message fields
        private string _questionCountError;
        private string _errorMessage;


        /// <summary>
        /// The name of the room to be created.
        /// </summary>
        public string RoomName
        {
            get => _roomName;
            set 
            {
                _roomName = value;
                OnPropertyChanged(); 
            }
        }

        /// <summary>
        /// The timeout duration for questions in the room.
        /// </summary>
        public double QuestionTimeout
        {
            get => _questionTimeout;
            set 
            {
                _questionTimeout = value;
                OnPropertyChanged(); 
            }
        }

        /// <summary>
        /// The maximum number of players allowed in the room.
        /// </summary>
        public uint MaxPlayers
        {
            get => _maxPlayers;
            set 
            {
                _maxPlayers = value;
                OnPropertyChanged(); 
            }
        }

        /// <summary>
        /// The total number of questions in the room.
        /// </summary>
        public uint QuestionsCount
        {
            get => _questionsCount;
            set 
            {
                _questionsCount = value;
                OnPropertyChanged();
            }
        }

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


        public string ErrorMessage
        {
            get => _errorMessage;
            set 
            {
                _errorMessage = value;
                OnPropertyChanged(); 
            }
        }






        
    }
}
