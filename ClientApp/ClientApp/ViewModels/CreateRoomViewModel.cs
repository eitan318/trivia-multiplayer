using System.Windows.Input;
using ClientApp.Commands;
using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Views.Pages;
using ClientApp.Stores;

namespace ClientApp.ViewModels
{
    /// <summary>
    /// ViewModel for the Create Room page, managing the room creation process and player data.
    /// </summary>
    class CreateRoomViewModel : ViewModelBase
    {
        private INavigationService _navigationService;
        private RoomDataStore _roomDataStore;
        private readonly RequestsExchangeService _requestsExchangeService;
        
        /// <summary>
        /// Private constructor for initializing the ViewModel.
        /// </summary>
        public CreateRoomViewModel(
            RequestsExchangeService requestsExchangeService,
            INavigationService navigationService,
            RoomDataStore roomDataStore) : base(true)
        {
            this._roomDataStore = roomDataStore;
            this._navigationService = navigationService;
            _requestsExchangeService = requestsExchangeService;
            CreateRoomCmd = new RelayCommand(PerformCreateRoom, CanCreateRoom);

            PropertyChanged += (sender, args) =>
            {
                if (args.PropertyName == nameof(RoomName) ||
                    args.PropertyName == nameof(MaxPlayers) ||
                    args.PropertyName == nameof(QuestionsCount) ||
                    args.PropertyName == nameof(QuestionTimeout))
                {
                    ((RelayCommand)CreateRoomCmd).RaiseCanExecuteChanged();
                }
            };

        }



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




        // Commands
        public ICommand CreateRoomCmd { get; }


        /// <summary>
        /// Determines whether the room can be created based on input validation.
        /// </summary>
        /// <returns>True if the room can be created, otherwise false.</returns>
        private bool CanCreateRoom()
        {
            return !string.IsNullOrWhiteSpace(RoomName?.Trim())
                   && MaxPlayers > 0
                   && QuestionsCount > 0
                   && QuestionTimeout > 0;
        }

        /// <summary>
        /// Executes the process of creating a room and fetching players.
        /// </summary>
        private async void PerformCreateRoom()
        {
            RoomDataModel? roomData = await CreateRoom();
            this._roomDataStore.CurrentRoomData = roomData;
            if (roomData != null)
            {
                this._navigationService.NavigateTo<AdminRoomViewModel>();
            }

        }


        /// <summary>
        /// Sends a request to create a room with the specified parameters.
        /// </summary>
        private async Task<RoomDataModel?> CreateRoom()
        {
            string trimmedRoomName = RoomName?.Trim();

            var createRoomRequest = new CreateRoomRequest(trimmedRoomName, MaxPlayers, QuestionsCount, QuestionTimeout);
            var responseInfo = await _requestsExchangeService.ExchangeRequest<CreateRoomResponse>(createRoomRequest);

            if (responseInfo.NormalResponse)
            {
                CreateRoomResponse createRoomResponse = responseInfo.Response;
                if (createRoomResponse.Status == 0)
                {
                    return createRoomResponse.RoomData;
                }
                else
                {
                    this.QuestionCountError = createRoomResponse.Errors.QuestionCountError;
                }

            }
            else
            {
                ErrorMessage = "SERVER ERROR: " + responseInfo.ErrorResponse.Message;
            }

            return null; 

        }
    }
}
