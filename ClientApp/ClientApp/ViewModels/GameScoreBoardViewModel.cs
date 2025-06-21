using ClientApp.Commands;
using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Models;
using ClientApp.Services;
using ClientApp.Stores;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Runtime.CompilerServices;

namespace ClientApp.ViewModels
{
    class GameScoreBoardViewModel : ScreenViewModelBase
    {
        private readonly RequestsExchangeService _requestsExchangeService;
        private readonly INavigationService _navigationService;
        private CancellationTokenSource _refreshRoomsCTS;
        private readonly int refreshMS = 300;
        private List<PlayerResults> _playersResults;
        public GameScoreBoardViewModel (RequestsExchangeService requestsExchangeService,
            INavigationService navigationService,
            AmIAdminStore amIAdminStore)
        {
            this._requestsExchangeService = requestsExchangeService;
            this._navigationService = navigationService;
            this.LeaveGameCmd = new LeaveGameCommand(navigationService, requestsExchangeService, null, amIAdminStore);
        }

        public List<PlayerResults> PlayersResults
        {
            get => _playersResults;
            set
            {
                _playersResults = value;
                OnPropertyChanged();
            }
        }

        public ICommand LeaveGameCmd { get; set; }

        public override async void OnNavigatedTo()
        {
            await GetPlayersResults();
            _refreshRoomsCTS = new CancellationTokenSource();
            Task.Run(() => PeriodicallyCheckGameStatus(_refreshRoomsCTS.Token)); 

        }

        public override void OnNavigatedAway()
        {
            _refreshRoomsCTS?.Cancel();
            _refreshRoomsCTS?.Dispose();
        }


        private async Task PeriodicallyCheckGameStatus(CancellationToken token)
        {
            try
            {
                while (!token.IsCancellationRequested)
                {

                    await CheckGameStatus();
                    await Task.Delay(refreshMS, token);
                }
            }
            catch (OperationCanceledException)
            {
                // Task was canceled; no further action needed
            }
        }

        private async Task CheckGameStatus()
        {
            GetGameStateRequest getRoomStatusRequest = new GetGameStateRequest();
            ResponseInfo<GetGameStateResponse> responseInfo =
                await _requestsExchangeService.ExchangeRequest<GetGameStateResponse>(getRoomStatusRequest);


            if (!responseInfo.NormalResponse)
                return;

            GetGameStateResponse response = responseInfo.Response;

            if (response.GameStatus == GameStatus.AnsweringQuestion)
                this._navigationService.NavigateTo<GameAnsweringViewModel>();

        }

        private async Task GetPlayersResults() 
        {
            GetGameResultRequest getPlayersResultsrequest = new GetGameResultRequest();
            ResponseInfo<GetGameResultsResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<GetGameResultsResponse>(getPlayersResultsrequest);
            
            if (!responseInfo.NormalResponse)
                return;
            GetGameResultsResponse playersResultsResponse = responseInfo.Response;
            this.PlayersResults = playersResultsResponse.Results;
        }

    }
}
