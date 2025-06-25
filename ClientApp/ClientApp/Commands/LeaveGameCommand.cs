using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.ViewModels;
using ClientApp.Stores;


namespace ClientApp.Commands
{
    public class LeaveGameCommand : CommandBase, IAsyncCommand
    {
        private readonly INavigationService _navigationService;
        private readonly RequestsExchangeService _requestsExchangeService;
        private readonly AmIAdminStore _amIAdminStore;
        private readonly Is1v1GameStore _is1v1GameStore;
        public LeaveGameCommand(INavigationService navigationService,
            RequestsExchangeService requestsExchangeService,
            AmIAdminStore amIAdminStore,
            Is1v1GameStore is1V1GameStore) 
        {
            this._is1v1GameStore = is1V1GameStore;
            this._amIAdminStore = amIAdminStore;
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService;
        }

        public override async Task ExecuteAsync(object parameter)
        {
            if(parameter is  GameAnsweringViewModel gameAnsweringViewModel)
            {
                gameAnsweringViewModel.Timer.Stop();
            }

            ResponseInfo<LeaveGameResponse> responseInfo = await _requestsExchangeService.
                ExchangeRequest<LeaveGameResponse>(RequestsCodes.LeaveGameRequest);

            if (!responseInfo.NormalResponse)
            {
                return;
            }
            LeaveGameResponse leaveGameResponse = responseInfo.Response;

            if(leaveGameResponse.Status != 0)
            {
                return;
            }

            if (_is1v1GameStore.is1v1Game)
            {
                _navigationService.NavigateTo<RoomAdminViewModel>();
            }
            else
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
        }
    }
}
