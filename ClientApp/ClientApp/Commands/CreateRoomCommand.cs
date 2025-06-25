using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Models;
using ClientApp.Services;
using ClientApp.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClientApp.Stores;

namespace ClientApp.Commands
{
    public class CreateRoomCommand : CommandBase, IAsyncCommand
    {
        private readonly INavigationService _navigationService;
        private RoomDataStore _roomDataStore;
        private readonly RequestsExchangeService _requestsExchangeService;
        public CreateRoomCommand(
            RequestsExchangeService requestsExchangeService,
            INavigationService navigationService,
            RoomDataStore roomDataStore)
        {
            this._roomDataStore = roomDataStore;
            this._navigationService = navigationService;
            this._requestsExchangeService = requestsExchangeService;
        }

        /// <summary>
        /// Determines whether the room can be created based on input validation.
        /// </summary>
        /// <returns>True if the room can be created, otherwise false.</returns>
        public override bool CanExecute(object parameters)
        {
            if(parameters is not CreateRoomViewModel createRoomViewModel)
            {
                return false;
            }
            return !string.IsNullOrWhiteSpace(_roomDataStore.CurrentRoomData.RoomName?.Trim())
                   && _roomDataStore.CurrentRoomData.MaxPlayers > 0
                   && _roomDataStore.CurrentRoomData.NumOfQuestionsInGame > 0
                   && _roomDataStore.CurrentRoomData.TimePerQuestion > 0;
        }

        /// <summary>
        /// Executes the process of creating a room and fetching players.
        /// </summary>
        public override async Task ExecuteAsync(object parameters)
        {
            if(parameters is not CreateRoomViewModel createRoomViewModel)
            {
                return;
            }
            RoomDataModel? roomData = await CreateRoom(createRoomViewModel);
            this._roomDataStore.CurrentRoomData = roomData;
            if (roomData != null)
            {
                this._navigationService.NavigateTo<RoomAdminViewModel>();
            }

        }


        /// <summary>
        /// Sends a request to create a room with the specified parameters.
        /// </summary>
        private async Task<RoomDataModel?> CreateRoom(CreateRoomViewModel createRoomViewModel)
        {
            string trimmedRoomName = _roomDataStore.CurrentRoomData.RoomName?.Trim();
            RoomDataModel trimmedRoomData = new RoomDataModel(_roomDataStore.CurrentRoomData);
            trimmedRoomData.RoomName = trimmedRoomData.RoomName.Trim();
            var createRoomRequest = new CreateRoomRequest(trimmedRoomData);

            var responseInfo = await _requestsExchangeService.ExchangeRequest<CreateRoomResponse>(createRoomRequest);

            if (responseInfo.NormalResponse)
            {
                CreateRoomResponse createRoomResponse = responseInfo.Response;
                if (createRoomResponse.Status == 0)
                {
                    return createRoomResponse.RoomData;
                }
                else
                {
                    createRoomViewModel.QuestionCountError = createRoomResponse.Errors.QuestionCountError;
                }
            }

            return null; 

        }
    }


}
