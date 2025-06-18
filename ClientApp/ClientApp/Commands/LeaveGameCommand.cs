using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.ViewModels;
using ClientApp.Stores;


namespace ClientApp.Commands
{
    class LeaveGameCommand : CommandBase
    {
        private readonly INavigationService _navigationService;
        private readonly RequestsExchangeService _requestsExchangeService;
        private readonly GameAnsweringViewModel _gameViewModel;
        private readonly AmIAdminStore _amIAdminStore;
        public LeaveGameCommand(INavigationService navigationService,
            RequestsExchangeService requestsExchangeService,
            GameAnsweringViewModel gameViewModel,
            AmIAdminStore amIAdminStore) 
        {
            this._amIAdminStore = amIAdminStore;
            this._gameViewModel = gameViewModel;
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService;
        }

        public override async void Execute(object parameter)
        {
            if (_gameViewModel != null)
            {
                _gameViewModel.Timer.Stop();
            }
            LeaveGameRequest request = new LeaveGameRequest();
            ResponseInfo<LeaveGameResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<LeaveGameResponse>(request);

            if (responseInfo.NormalResponse)
            {
                LeaveGameResponse leaveGameResponse = responseInfo.Response;

                if(leaveGameResponse.Status == 0)
                {
                    if (_amIAdminStore.AmIAdmin)
                    {
                        _navigationService.NavigateTo<RoomAdminViewModel>();
                    }
                    else
                    {
                        _navigationService.NavigateTo<RoomMemberViewModel>();
                    }
                }
                else
                {

                } 
            }
        }
    }
}
