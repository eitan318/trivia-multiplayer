using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Stores;
using ClientApp.ViewModels;

namespace ClientApp.Commands
{
    class LeaveRoomCommand : CommandBase
    {
        private INavigationService _navigationService;
        private readonly RequestsExchangeService _requestsExchangeService;
        private JoinRoomViewModel _joinRoomViewModel;
        public LeaveRoomCommand(
            JoinRoomViewModel joinRoomViewModel,
            INavigationService navigationService,
            RequestsExchangeService requestsExchangeService,
            RoomDataStore roomDataStore
            )
        {
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService;
            this._joinRoomViewModel = joinRoomViewModel;
        }
        public override async void Execute(object parameter)
        {
            var leaverRoomRequest = new LeaveRoomRequest();
            ResponseInfo<LeaveRoomResponse> responseInfo =
                await _requestsExchangeService.ExchangeRequest<LeaveRoomResponse>(leaverRoomRequest);
            LeaveRoomResponse response = (LeaveRoomResponse)responseInfo.Response;
            if (response.Status == 0)
            {
                this._navigationService.NavigateTo<MenuViewModel>();
            }

        }

    }
}
