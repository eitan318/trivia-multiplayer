using ClientApp.Commands;
using ClientApp.Models.Responses;
using ClientApp.Services;
using System.Windows.Input;
using ClientApp.Models.Requests;
using ClientApp.Stores;
using System.Diagnostics;

namespace ClientApp.ViewModels
{
    class Waiting1v1ViewModel : ScreenViewModelBase
    {

        private CancellationTokenSource _refreshRoomsCTS;
        private readonly int refreshMS = 300;
        private RequestsExchangeService _requestsExchangeService;
        private readonly RoomDataStore _roomDataStore;
        public Waiting1v1ViewModel(
            LeaveWaitingListCommand leaveWaitingListCommand,
            Join1v1WaitingListCommand join1V1WaitingListCommand,
            Set1v1GameSettingsCommand set1v1GameSettingsCommand,
            RequestsExchangeService requestsExchangeService,
            NavigateCommand<GameAnsweringViewModel> start1v1GameCommand, 
            AmIAdminStore amIAdminStore,
            Is1v1GameStore is1V1GameStore)
        {
            amIAdminStore.AmIAdmin = false;
            is1V1GameStore.is1v1Game = true;

            this._set1v1GameSettingsCmd = set1v1GameSettingsCommand;

            this.LeaveWaitingListCmd = leaveWaitingListCommand;
            this.Start1v1GameCommand = start1v1GameCommand;
            this._requestsExchangeService = requestsExchangeService;
        }


        private IAsyncCommand _set1v1GameSettingsCmd;
        public IAsyncCommand LeaveWaitingListCmd { get; set; }
        public ICommand Start1v1GameCommand { get; set; }

        public override async void OnNavigatedTo()
        {
            base.OnNavigatedTo();

            // Execute the command asynchronously
            try
            {
                if (_set1v1GameSettingsCmd is IAsyncCommand asyncCommand)
                {
                    await asyncCommand.ExecuteAsync(null);
                }
                else
                {
                    _set1v1GameSettingsCmd.Execute(null);
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine($"Error executing _set1v1GameSettingsCmd: {ex.Message}");
            }

            // Start the periodic check
            _refreshRoomsCTS = new CancellationTokenSource();
            _ = PeriodicallyCheckForMatch(_refreshRoomsCTS.Token);
        }



        public override void OnNavigatedAway()
        {
            base.OnNavigatedAway();
            _refreshRoomsCTS?.Cancel();
            _refreshRoomsCTS?.Dispose();
        }

        private string _errorMesage;
        public string ErrorMessage
        {
            get { return _errorMesage; }
            set { 
                _errorMesage = value;
                OnPropertyChanged();
            }
        }

        private async Task PeriodicallyCheckForMatch(CancellationToken token)
        {
            try
            {
                while (!token.IsCancellationRequested)
                {
                    await CheckForMatch();
                    await Task.Delay(refreshMS, token); // Pass the token to enable cancellation
                }
            }
            catch (OperationCanceledException)
            {
                // Task was canceled; no further action needed
            }
        }

        private async Task CheckForMatch()
        {
            ResponseInfo<DidFound1v1MatchResponse> responseInfo = await _requestsExchangeService.
                ExchangeRequest<DidFound1v1MatchResponse>(RequestsCodes.DidFound1v1MatchRequest);

            if (!responseInfo.NormalResponse) 
            {
                return;
            }

            if (responseInfo.Response.Status != 0) 
            {
                this.ErrorMessage = responseInfo.Response.Errors.GeneralError;
            }
            if (responseInfo.Response.FoundMatch)
            {
                this.Start1v1GameCommand.Execute(null);
            }
        }


    }
}
