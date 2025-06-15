using ClientApp.Stores;
using ClientApp.Models;
using ClientApp.Services;
using ClientApp.Commands;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using System.Windows.Input;

namespace ClientApp.ViewModels
{
    class GameResultsViewModel : ViewModelBase
    {
        private List<PlayerResults> _players;
        private readonly RequestsExchangeService _requestsExchangeService;
        private CancellationTokenSource _refreshTopPlayersCTS;
        public List<PlayerResults> Players
        {
            get => _players;
            set
            {
                _players = value;
                OnPropertyChanged();
            }
        }

        public GameResultsViewModel(
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService) : base(false)
        {
            LeaveGameCmd = new LeaveGameCommand(navigationService, requestsExchangeService, null);
            this._requestsExchangeService = requestsExchangeService;
        }

        public ICommand LeaveGameCmd { get; }


        public override void OnNavigatedTo()
        {
            _refreshTopPlayersCTS = new CancellationTokenSource();
            Task.Run(() => PeriodicallyRefreshAllPlayersResults(_refreshTopPlayersCTS.Token));
        }

        public override void OnNavigatedAway()
        {
            _refreshTopPlayersCTS?.Cancel();
            _refreshTopPlayersCTS?.Dispose();
        }
        private async Task PeriodicallyRefreshAllPlayersResults(CancellationToken token)
        {
            try
            {
                while (!token.IsCancellationRequested)
                {
                    await getAllPlayersResults();
                    await Task.Delay(1000, token); // Pass the token to enable cancellation
                }
            }
            catch (OperationCanceledException)
            {
                // Task was canceled; no further action needed
            }
        }

        public async Task getAllPlayersResults()
        {
            GetGameResultRequest getPlayersResultsrequest = new GetGameResultRequest();
            var responseInfo = await _requestsExchangeService.ExchangeRequest<GetGameResultsResponse>(getPlayersResultsrequest);
            if (responseInfo.NormalResponse)
            {
                GetGameResultsResponse playersResultsResponse = responseInfo.Response;
                this.Players = playersResultsResponse.Results;
            }
        }
    }
}
