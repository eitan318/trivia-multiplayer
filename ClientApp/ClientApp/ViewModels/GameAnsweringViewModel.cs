using System.Windows.Input;
using ClientApp.Commands;
using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Stores;

namespace ClientApp.ViewModels
{
    class GameAnsweringViewModel : ViewModelBase
    {
        private readonly RequestsExchangeService _requestsExchangeService;

        private readonly int _msTimerInterval = 300;

        private readonly CountdownTimerViewModel _countdownTimerViewModel;
        public CountdownTimerViewModel Timer => _countdownTimerViewModel;

        public GameAnsweringViewModel(RequestsExchangeService requestsExchangeService,
            RoomDataStore roomDataStore, INavigationService navigationService, AmIAdminStore amIAdminStore) : base(false)
        {
            _roomDataStore = roomDataStore;
            _requestsExchangeService = requestsExchangeService;

            SubmitCmd = new SubmitAnswerCommand(requestsExchangeService, this, navigationService);
            LeaveGameCmd = new LeaveGameCommand(navigationService, requestsExchangeService, this, amIAdminStore);

            _countdownTimerViewModel = new CountdownTimerViewModel(_msTimerInterval);


            _countdownTimerViewModel.TimerEnded += async (sender, args) => await HandleTimerEndAsync();
        }
        
        public override async void OnNavigatedTo()
        {
            SelectedAnswerIndex = -1;
            await NextQuestion();
        }
        public override async void OnNavigatedAway()
        {
            this.Timer.Stop();
        }


        public ICommand SubmitCmd { get; }
        public ICommand LeaveGameCmd { get; }
        
        private readonly RoomDataStore _roomDataStore;

        private uint _questionNumber;
        private QuestionInfo _questionInfo;
        private string _errorMessage;
        public async Task NextQuestion()
        {
            try
            {
                var getQuestionRequest = new GetQuestionRequest();
                var questionResponseInfo = await _requestsExchangeService.ExchangeRequest<GetQuestionResponse>(getQuestionRequest);


                if (questionResponseInfo.NormalResponse)
                {
                    if (questionResponseInfo.Response?.Status == 0)
                    {
                        App.Current.Dispatcher.Invoke(() =>
                        {
                            SelectedAnswerIndex = -1;
                            QuestionInfo = questionResponseInfo.Response.Question;
                            QuestionNumber = questionResponseInfo.Response.QuestionNumber;
                        });
                    }
                    else
                    {
                        ErrorMessage = "Unable to fetch the question. Please try again.";
                    }

                }

                Timer.Reset(TimeSpan.FromSeconds(_roomDataStore.CurrentRoomData.TimePerQuestion));
                Timer.Start();
            }
            catch (Exception ex)
            {
                ErrorMessage = $"An error occurred: {ex.Message}";
            }
        }


        private async Task HandleTimerEndAsync()
        {
            SubmitCmd.Execute(null);
        }



        public string QDisplay => $"{QuestionNumber}/{_roomDataStore.CurrentRoomData.NumOfQuestionsInGame}";


        private int _selectedAnswerIndex = -1; // -1 indicates no selection
        public int SelectedAnswerIndex
        {
            get => _selectedAnswerIndex;
            set
            {
                if (_selectedAnswerIndex != value)
                {
                    _selectedAnswerIndex = value;
                    OnPropertyChanged();

                    if (SubmitCmd is SubmitAnswerCommand submitCommand)
                    {
                        submitCommand.RaiseCanExecuteChanged();
                    }
                }
            }
        }






        public QuestionInfo QuestionInfo
        {
            get => _questionInfo;
            set
            {
                _questionInfo = value;
                OnPropertyChanged();
            }
        }


        public uint QuestionNumber
        {
            get => _questionNumber;
            set
            {
                _questionNumber = value;
                OnPropertyChanged();
                OnPropertyChanged(nameof(QDisplay)); 
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
