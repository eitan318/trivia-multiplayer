using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.Stores;
using System.Windows.Media.Animation;
using System.Diagnostics;
using ClientApp.Models;

namespace ClientApp.Commands
{
    class Set1v1GameSettingsCommand : CommandBase, IAsyncCommand
    {
        private readonly RoomDataStore _roomDataStore;
        private readonly RequestsExchangeService _requestExchangeService;
        public Set1v1GameSettingsCommand(RoomDataStore roomDataStore,
            RequestsExchangeService requestsExchangeService) {
            this._roomDataStore = roomDataStore;
            this._requestExchangeService = requestsExchangeService;
        }

        public override async Task ExecuteAsync(object parameter)
        {
            try
            {
                ResponseInfo<Get1v1GameSettingsResponse> responseInfo = await this._requestExchangeService
                    .ExchangeRequest<Get1v1GameSettingsResponse>(RequestsCodes.Get1v1GameDataResquest);

                if (!responseInfo.NormalResponse)
                {
                    return;
                }

                if (responseInfo.Response.Status != 0)
                {
                    return;
                }

                this._roomDataStore.CurrentRoomData = responseInfo.Response.GameSettigns;
            }
            catch (Exception ex)
            {
                // Log or handle any unexpected errors
                Debug.WriteLine($"Error in Set1v1GameSettingsCommand: {ex.Message}");
            }
        }


    }
}
