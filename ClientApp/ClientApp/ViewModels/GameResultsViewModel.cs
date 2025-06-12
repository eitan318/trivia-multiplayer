using ClientApp.Stores;
using ClientApp.Models;
using ClientApp.Services;
using ClientApp.Commands;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;

namespace ClientApp.ViewModels
{
    class GameResultsViewModel : ViewModelBase
    {
        private List<PlayerResults> _players;
        private readonly RequestsExchangeService _requestsExchangeService;
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
            this._requestsExchangeService = requestsExchangeService;
            getAllPlayersResults();
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
