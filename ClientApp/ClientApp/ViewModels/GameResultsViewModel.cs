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
        private List<PlayerResults> _playersResults;
        private readonly RequestsExchangeService _requestsExchangeService;
        private CancellationTokenSource _refreshTopPlayersCTS;
        private readonly int refreshMS = 300;
        public List<PlayerResults> PlayersResults
        {
            get => _playersResults;
            set
            {
                _playersResults = value;
                OnPropertyChanged();
            }
        }

        public GameResultsViewModel(
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService,
            AmIAdminStore amIAdminStore) : base(false)
        {
            LeaveGameCmd = new LeaveGameCommand(navigationService, requestsExchangeService, null, amIAdminStore);
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
                    await Task.Delay(refreshMS, token);
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
            if (!responseInfo.NormalResponse)
                return;
            GetGameResultsResponse playersResultsResponse = responseInfo.Response;
            this.PlayersResults = playersResultsResponse.Results;
        }
    }
}
