using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows.Input;
using ClientApp.Commands;
using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Enums;

namespace ClientApp.ViewModels
{
    /// <summary>
    /// ViewModel for the Create Room page, managing the room creation process and player data.
    /// </summary>
    class CreateRoomPageViewModel : BaseViewModel
    {
        private string _roomName;
        private uint _questionTimeout;
        private bool _isPlayerGridVisible;
        private uint _maxPlayers;
        private uint _questionsCount;
        private string _questionCountError;

        /// <summary>
        /// The name of the room to be created.
        /// </summary>
        public string RoomName
        {
            get => _roomName;
            set { _roomName = value; OnPropertyChanged(); }
        }

        /// <summary>
        /// The timeout duration for questions in the room.
        /// </summary>
        public uint QuestionTimeout
        {
            get => _questionTimeout;
            set { _questionTimeout = value; OnPropertyChanged(); }
        }

        /// <summary>
        /// The maximum number of players allowed in the room.
        /// </summary>
        public uint MaxPlayers
        {
            get => _maxPlayers;
            set { _maxPlayers = value; OnPropertyChanged(); }
        }

        /// <summary>
        /// The total number of questions in the room.
        /// </summary>
        public uint QuestionsCount
        {
            get => _questionsCount;
            set { _questionsCount = value; OnPropertyChanged(); }
        }

        /// <summary>
        /// Error message related to the number of questions.
        /// </summary>
        public string QuestionCountErrort
        {
            get => _questionCountError;
            set { _questionCountError = value; OnPropertyChanged(); }
        }

        /// <summary>
        /// Indicates whether the player grid is visible.
        /// </summary>
        public bool IsPlayerGridVisible
        {
            get => _isPlayerGridVisible;
            set { _isPlayerGridVisible = value; OnPropertyChanged(); }
        }

        /// <summary>
        /// Collection of players currently in the room.
        /// </summary>
        public ObservableCollection<Player> Players { get; set; } = new ObservableCollection<Player>();

        /// <summary>
        /// Command to create a new room.
        /// </summary>
        public ICommand CreateRoomCommand { get; }

        /// <summary>
        /// Private constructor for initializing the ViewModel.
        /// </summary>
        private CreateRoomPageViewModel()
        {
            CreateRoomCommand = new RelayCommand(PerformCreateRoom, CanCreateRoom);
            IsPlayerGridVisible = false;

            PropertyChanged += (sender, args) =>
            {
                if (args.PropertyName == nameof(RoomName) ||
                    args.PropertyName == nameof(MaxPlayers) ||
                    args.PropertyName == nameof(QuestionsCount) ||
                    args.PropertyName == nameof(QuestionTimeout))
                {
                    ((RelayCommand)CreateRoomCommand).RaiseCanExecuteChanged();
                }
            };

        }

        /// <summary>
        /// Creates or retrieves a singleton instance of the CreateRoomPageViewModel.
        /// </summary>
        /// <returns>An instance of CreateRoomPageViewModel.</returns>
        public static CreateRoomPageViewModel Instance()
        {
            return GetInstance(() => new CreateRoomPageViewModel());
        }

        /// <summary>
        /// Determines whether the room can be created based on input validation.
        /// </summary>
        /// <param name="parameter">Unused parameter.</param>
        /// <returns>True if the room can be created, otherwise false.</returns>
        private bool CanCreateRoom(object parameter)
        {
            return !string.IsNullOrWhiteSpace(RoomName)
                   && MaxPlayers > 0
                   && QuestionsCount > 0
                   && QuestionTimeout > 0;
        }

        /// <summary>
        /// Executes the process of creating a room and fetching players.
        /// </summary>
        /// <param name="parameter">Unused parameter.</param>
        private async void PerformCreateRoom(object parameter)
        {
            IsPlayerGridVisible = true;
            CreateRoom();
            PutPlayers();
        }

        /// <summary>
        /// Sends a request to retrieve and populate the player list for the room.
        /// </summary>
        private async void PutPlayers()
        {
            var getPlayersRequest = new GetPlayersRequest();
            ResponseInfo responseInfo = await RequestsExchangeService.ExchangeRequest(getPlayersRequest);

            if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
            {
                // Handle error appropriately.
                return;
            }

            var response = JsonResponseDeserialize.DeserializeResponse<GetPlayersResponse>(responseInfo);
            var playerNames = response.Players;

            foreach (var playerName in playerNames)
            {
                Players.Add(new Player { Username = playerName });
            }
        }

        /// <summary>
        /// Sends a request to create a room with the specified parameters.
        /// </summary>
        private async void CreateRoom()
        {
            var createRoomRequest = new CreateRoomRequest(RoomName, MaxPlayers, QuestionsCount, QuestionTimeout);
            var responseInfo = await RequestsExchangeService.ExchangeRequest(createRoomRequest);

            if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
            {
                // Handle error appropriately.
                return;
            }

            NoDataResponse createRoomResponse = JsonResponseDeserialize.DeserializeResponse<NoDataResponse>(responseInfo);

            switch (createRoomResponse.Status)
            {
                case (byte)CreateRoomResponseStatus.Success:
                    break;
                case (byte)CreateRoomResponseStatus.TooMuchQuestions:
                    this.QuestionCountErrort = "Too much questions";
                    break;
            }
        }
    }
}
