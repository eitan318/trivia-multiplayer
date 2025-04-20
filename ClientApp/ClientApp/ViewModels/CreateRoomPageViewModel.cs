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

namespace ClientApp.ViewModels
{
    class CreateRoomPageViewModel : BaseViewModel
    {
        private string _roomName;
        private uint _questionTimeout;
        private bool _isPlayerGridVisible;
        private uint _maxPlayers;
        private uint _questionsCount;

        public string RoomName
        {
            get => _roomName;
            set { _roomName = value; OnPropertyChanged(); }
        }

        public uint QuestionTimeout
        {
            get => _questionTimeout;
            set { _questionTimeout = value; OnPropertyChanged(); }
        }

        public uint MaxPlayers
        {
            get => _maxPlayers;
            set { _maxPlayers = value; OnPropertyChanged(); }
        }

        public uint QuestionsCount
        {
            get => _questionsCount;
            set { _questionsCount = value; OnPropertyChanged(); }
        }

        public bool IsPlayerGridVisible
        {
            get => _isPlayerGridVisible;
            set { _isPlayerGridVisible = value; OnPropertyChanged(); }
        }

        public ObservableCollection<Player> Players { get; set; } = new ObservableCollection<Player>();

        public ICommand CreateRoomCommand { get; }

        private CreateRoomPageViewModel()
        {
            CreateRoomCommand = new RelayCommand(CreateRoom, CanCreateRoom);
            IsPlayerGridVisible = false; // Ensure it starts hidden.

            // Listen to property changes to refresh CanExecute state.
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

        public static CreateRoomPageViewModel Instance()
        {
            return GetInstance(() => new CreateRoomPageViewModel());
        }

        private bool CanCreateRoom(object parameter)
        {
            return !string.IsNullOrWhiteSpace(RoomName)
                   && MaxPlayers > 0
                   && QuestionsCount > 0
                   && QuestionTimeout > 0;
        }


        private async void CreateRoom(object parameter)
        {
            IsPlayerGridVisible = true;

            var createRoomRequest = new CreateRoomRequest(RoomName, MaxPlayers, QuestionsCount, QuestionTimeout);
            var responseInfo = await RequestsExchangeService.ExchangeRequest(createRoomRequest);
            if (responseInfo.Code == (byte)ResponsesCodes.ErrorResponse)
            {
                // Handle error appropriately.
                return;
            }
            else
            {
                NoDataResponse createRoomResponse = JsonResponseDeserialize.DeserializeResponse<NoDataResponse>(responseInfo);
                if(createRoomResponse.Status != 0)
                {
                    string[] errMsg = new string[]
                    {
                         "",
                    };
                    //TODO: implement err msg
                }

            }

            var getPlayersRequest = new GetPlayersRequest();
            responseInfo = await RequestsExchangeService.ExchangeRequest(getPlayersRequest);

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
    }
}
