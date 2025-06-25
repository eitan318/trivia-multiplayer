using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Stores;
using ClientApp.ViewModels;

namespace ClientApp.Commands
{
    class LeaveRoomCommand : CommandBase, IAsyncCommand
    {
        private INavigationService _navigationService;
        private readonly RequestsExchangeService _requestsExchangeService;
        public LeaveRoomCommand(
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService,
            RoomDataStore roomDataStore
            )
        {
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService;
        }
        public override async void Execute(object parameter)
        {
                var leaverRoomRequest = new LeaveRoomRequest();
                ResponseInfo<LeaveRoomResponse> responseInfo =
                    await _requestsExchangeService.ExchangeRequest<LeaveRoomResponse>(leaverRoomRequest);
                if (!responseInfo.NormalResponse)
                    return;
                LeaveRoomResponse response = responseInfo.Response;
                if (response.Status == 0)
                {
                    this._navigationService.NavigateTo<MenuViewModel>();
                }
                else
                {
                    throw new Exception();
                }

        }

    }
}
