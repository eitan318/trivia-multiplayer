using ClientApp.Commands;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Models;
using ClientApp.Services;

namespace ClientApp.ViewModels
{

    class HighScoresViewModel : ScreenViewModelBase
    {
        private readonly RequestsExchangeService _requestsExchangeService;
        private readonly int amountTopPlayers = 3;
        private CancellationTokenSource _refreshTopPlayersCTS;

        public HighScoresViewModel(RequestsExchangeService requestsExchangeService,
            TopBarViewModel topBarViewModel) : base(true, topBarViewModel)
        {
            _requestsExchangeService = requestsExchangeService;
        }

        


        public override void OnNavigatedTo()
        {
            _refreshTopPlayersCTS = new CancellationTokenSource();
            Task.Run(() => PeriodicallyRefreshTopPlayers(_refreshTopPlayersCTS.Token)); 
        }

        public override void OnNavigatedAway()
        {
            _refreshTopPlayersCTS?.Cancel();
            _refreshTopPlayersCTS?.Dispose();
        }

        // Fields
        private List<HighScoreInfoModel> responseList;
        
        // Error mesasge fields
        private string _errorMessage;

        // Properties

        public List<HighScoreInfoModel> ResponseList
        {
            get => responseList;
            set
            {
                responseList = value;
                OnPropertyChanged();
            }
        }
        
        
        
        // Error message properties
        public string ErrorMessage
        {
            get => _errorMessage;
            set
            {
                _errorMessage = value;
                OnPropertyChanged();
            }
        }

        private async Task PeriodicallyRefreshTopPlayers(CancellationToken token)
        {
            try
            {
                while (!token.IsCancellationRequested)
                {
                    await RefreshTop();
                    await Task.Delay(5000, token); // Pass the token to enable cancellation
                }
            }
            catch (OperationCanceledException)
            {
                // Task was canceled; no further action needed
            }
        }


        /// <summary>
        /// This function refreshes the top leading players
        /// </summary>
        public async Task RefreshTop()
        { 
            try
            {
                HighScoresRequest request = new HighScoresRequest(this.amountTopPlayers);
                var responseInfo = await _requestsExchangeService.ExchangeRequest<HighScoresResponse>(request);

                if (responseInfo.NormalResponse)
                {
                    var HighestScoresResponse = responseInfo.Response;
                    this.ResponseList = HighestScoresResponse.Statistics;
                }

            }
            catch (Exception ex)
            {
                ErrorMessage = $"Error retrieving top users: {ex.Message}";
            }
        }

    }
}
