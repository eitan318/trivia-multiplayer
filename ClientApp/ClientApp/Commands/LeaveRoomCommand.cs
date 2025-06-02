using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Stores;
using ClientApp.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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


        }

    }
}
