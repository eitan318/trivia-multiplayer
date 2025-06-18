using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Models;
using System.Windows.Input;
using ClientApp.Commands;
using ClientApp.Stores;

namespace ClientApp.ViewModels
{
    class WaitingBetweenQuestionsViewModel : ViewModelBase
    {
        private readonly RequestsExchangeService _requestsExchangeService;
        private readonly INavigationService _navigationService;
        private CancellationTokenSource _refreshRoomsCTS;
        private readonly int refreshMS = 300;

        public WaitingBetweenQuestionsViewModel(RequestsExchangeService requestsExchangeService,
            INavigationService navigationService,
            AmIAdminStore amIAdminStore)
        {
            this._requestsExchangeService = requestsExchangeService;
            this._navigationService = navigationService;
            this.LeaveGameCmd = new LeaveGameCommand(navigationService, requestsExchangeService, null, amIAdminStore);
        }

        public ICommand LeaveGameCmd { get; set; }

        public override void OnNavigatedTo()
        {
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
                    await Task.Delay(refreshMS, token); // Pass the token to enable cancellation
                }
            }
            catch (OperationCanceledException)
            {
                // Task was canceled; no further action needed
            }
        }

        private async Task CheckGameStatus()
        {
            var getRoomStatusRequest = new GetGameStateRequest();
            ResponseInfo<GetGameStateResponse> responseInfo =
                await _requestsExchangeService.ExchangeRequest<GetGameStateResponse>(getRoomStatusRequest);

            if (!responseInfo.NormalResponse)
                return;

            GetGameStateResponse response = responseInfo.Response;

            if (response.GameStatus == GameStatus.ScoreBoardShow)
                this._navigationService.NavigateTo<GameScoreBoardViewModel>();
            if (response.GameStatus == GameStatus.GameResultsShow)
                this._navigationService.NavigateTo<GameResultsViewModel>();
        }

    }
}
