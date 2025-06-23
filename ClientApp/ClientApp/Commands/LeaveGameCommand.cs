using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.ViewModels;
using ClientApp.Stores;


namespace ClientApp.Commands
{
    public class LeaveGameCommand : CommandBase
    {
        private readonly INavigationService _navigationService;
        private readonly RequestsExchangeService _requestsExchangeService;
        private readonly AmIAdminStore _amIAdminStore;
        public LeaveGameCommand(INavigationService navigationService,
            RequestsExchangeService requestsExchangeService,
            AmIAdminStore amIAdminStore) 
        {
            this._amIAdminStore = amIAdminStore;
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService;
        }

        public override async void Execute(object parameter)
        {
            if(parameter is  GameAnsweringViewModel gameAnsweringViewModel)
            {
                gameAnsweringViewModel.Timer.Stop();
            }

            ResponseInfo<LeaveGameResponse> responseInfo = await _requestsExchangeService.
                ExchangeRequest<LeaveGameResponse>(RequestsCodes.LeaveGameRequest);

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
