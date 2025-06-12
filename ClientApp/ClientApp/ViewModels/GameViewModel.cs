using ClientApp.Commands;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Models;
using ClientApp.Services;
using ClientApp.Stores;
using System.Windows.Input;

namespace ClientApp.ViewModels
{
    class GameViewModel : ViewModelBase
    {
        private readonly RequestsExchangeService _requestsExchangeService;
        private readonly CountdownTimerViewModel _countdownTimerViewModel;
        private readonly RoomDataStore _roomDataStore;

        private uint _totalQuestions;
        private uint _questionNumber;
        private string _question;
        private List<string> _possibleAnswers;
        private QuestionInfo _questionInfo;
        private double _score;

        public GameViewModel(RequestsExchangeService requestsExchangeService,
            RoomDataStore roomDataStore, INavigationService navigationService) : base(false)
        {
            _roomDataStore = roomDataStore;
            _requestsExchangeService = requestsExchangeService;
            _countdownTimerViewModel = new CountdownTimerViewModel();
            SubmitCmd = new SubmitAnswerCommand(requestsExchangeService, this, roomDataStore, navigationService);

            // Subscribe to the TimerEnded event
            _countdownTimerViewModel.TimerEnded += OnTimerEnded;

            _questionNumber = 0;
            _totalQuestions = _roomDataStore.CurrentRoomData.NumOfQuestionsInGame;
            PossibleAnswers = new List<string>();

            // Debug initialization
            Console.WriteLine("GameViewModel initialized.");
        }

        public ICommand SubmitCmd { get; }

        public CountdownTimerViewModel Timer => _countdownTimerViewModel;

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

                    // Notify SubmitCmd that CanExecute might have changed
                    if (SubmitCmd is SubmitAnswerCommand submitCommand)
                    {
                        submitCommand.RaiseCanExecuteChanged();
                    }
                }
            }
        }

        public async void NextQuestion()
        {
            QuestionNumber++;

            // Debugging log
            Console.WriteLine($"Loading question {QuestionNumber}...");

            var getQuestionRequest = new GetQuestionRequest();
            var questionResponseInfo = await _requestsExchangeService.ExchangeRequest<GetQuestionResponse>(getQuestionRequest);

            if (questionResponseInfo.NormalResponse)
            {
                var getQuestionResponse = questionResponseInfo.Response;
                if (getQuestionResponse.Status == 0)
                {
                    SelectedAnswerIndex = -1;
                    QuestionInfo = getQuestionResponse.Question;
                    Question = QuestionInfo.Question;
                    PossibleAnswers = QuestionInfo.PossibleAnswers;
                }
                else
                {
                    // Handle response status != 0
                }
            }

            // Reset and start the timer for the next question
            Timer.Reset(_roomDataStore.CurrentRoomData.TimePerQuestion);
            Timer.Start();

            // Debugging log
            Console.WriteLine($"Timer reset to {_roomDataStore.CurrentRoomData.TimePerQuestion} seconds and started.");
        }

        public override void OnNavigatedTo()
        {
            NextQuestion();
        }

        private void OnTimerEnded(object sender, EventArgs e)
        {
            this.SubmitCmd.Execute(null);
            NextQuestion();
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

        public string QDisplay => $"{QuestionNumber}/{TotalQuestions}";

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
