using System.Windows.Input;
using ClientApp.Commands;
using ClientApp.Models;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Stores;

namespace ClientApp.ViewModels
{
    class GameViewModel : ViewModelBase
    {
        private readonly RequestsExchangeService _requestsExchangeService;

        private readonly RoomDataStore _roomDataStore;

        private uint _totalQuestions;
        private uint _questionNumber;
        private string _question;
        private List<string> _possibleAnswers;
        private QuestionInfo _questionInfo;
        private double _score;
        private readonly int _msTimerInterval = 1000;

        private readonly CountdownTimerViewModel _countdownTimerViewModel;
        public CountdownTimerViewModel Timer => _countdownTimerViewModel;

        public GameViewModel(RequestsExchangeService requestsExchangeService,
            RoomDataStore roomDataStore, INavigationService navigationService) : base(false)
        {
            _roomDataStore = roomDataStore;
            _requestsExchangeService = requestsExchangeService;

            SubmitCmd = new SubmitAnswerCommand(requestsExchangeService, this, navigationService);
            LeaveGameCmd = new LeaveGameCommand(navigationService, requestsExchangeService, this);


            _countdownTimerViewModel = new CountdownTimerViewModel(_msTimerInterval);
            PossibleAnswers = new List<string>();
        }

        public ICommand SubmitCmd { get; }
        public ICommand LeaveGameCmd { get; }



        public string QDisplay => $"{QuestionNumber}/{TotalQuestions}";


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

        public async Task NextQuestion()
        {
            try
            {
                QuestionNumber++;

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
                            Question = QuestionInfo.Question;
                            PossibleAnswers = QuestionInfo.PossibleAnswers;
                        });
                    }
                    else
                    {
                        Question = "Unable to fetch the question. Please try again.";
                        PossibleAnswers = new List<string>();
                    }

                }

                Timer.Reset(TimeSpan.FromSeconds(_roomDataStore.CurrentRoomData.TimePerQuestion));
                Timer.Start();
            }
            catch (Exception ex)
            {
                Question = $"An error occurred: {ex.Message}";
                PossibleAnswers = new List<string>();
            }
        }

        public override async void OnNavigatedTo()
        {
            _questionNumber = 0;
            _totalQuestions = _roomDataStore.CurrentRoomData.NumOfQuestionsInGame;
             _countdownTimerViewModel.TimerEnded += async (sender, args) => await HandleTimerEndAsync();

            Timer.Reset(TimeSpan.FromSeconds(10));
            Timer.Start();  
            await NextQuestion();
        }

        private async Task HandleTimerEndAsync()
        {
            SubmitCmd.Execute(null);
        }

        public uint TotalQuestions
        {
            get => _totalQuestions;
            set
            {
                _totalQuestions = value;
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


        public string Question
        {
            get => _question;
            set
            {
                _question = value;
                OnPropertyChanged();
            }
        }

        public List<string> PossibleAnswers
        {
            get => _possibleAnswers;
            set
            {
                _possibleAnswers = value;
                OnPropertyChanged();
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

        public double Score
        {
            get => _score;
            set
            {
                _score = value;
                OnPropertyChanged();
            }
        }
    }
}
