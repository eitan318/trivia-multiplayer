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
using ClientApp.Views.Pages;

namespace ClientApp.ViewModels
{
    /// <summary>
    /// ViewModel for the Create Room page, managing the room creation process and player data.
    /// </summary>
    class CreateRoomPageViewModel : BaseViewModel
    {
        private string _roomName;
        private uint _questionTimeout = 1; //Min val from xaml

        private uint _maxPlayers = 1; //Min val from xaml
        private uint _questionsCount = 1; //Min val from xaml
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
        /// Command to create a new room.
        /// </summary>
        public ICommand CreateRoomCommand { get; }

        /// <summary>
        /// Private constructor for initializing the ViewModel.
        /// </summary>
        private CreateRoomPageViewModel()
        {
            CreateRoomCommand = new RelayCommand(PerformCreateRoom, CanCreateRoom);

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
            uint? roomId = await CreateRoom();
            if (roomId != null)
            {
                MyNavigationService.Navigate(new RoomPage(roomId.Value));
            }


        }


        /// <summary>
        /// Sends a request to create a room with the specified parameters.
        /// </summary>
        private async Task<uint?> CreateRoom()
        {
            var createRoomRequest = new CreateRoomRequest(RoomName, MaxPlayers, QuestionsCount, QuestionTimeout);
            var responseInfo = await RequestsExchangeService.ExchangeRequest(createRoomRequest);

            if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
            {
                // Handle error appropriately.
                return null;
            }

            CreateRoomResponse createRoomResponse = JsonResponseDeserialize.DeserializeResponse<CreateRoomResponse>(responseInfo);


            switch (createRoomResponse.Status)
            {
                case (byte)CreateRoomResponseStatus.Success:
                    return createRoomResponse.RoomId;
                case (byte)CreateRoomResponseStatus.TooMuchQuestions:
                    this.QuestionCountErrort = "Too much questions";
                    break;
            }
            return null;
        }
    }
}
