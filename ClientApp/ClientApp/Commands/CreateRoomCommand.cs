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
    class CreateRoomCommand : CommandBase
    {
        private CreateRoomViewModel _createRoomViewModel;
        private readonly INavigationService _navigationService;
        private RoomDataStore _roomDataStore;
        private readonly RequestsExchangeService _requestsExchangeService;
        public CreateRoomCommand(
            CreateRoomViewModel createRoomViewModel,
            RequestsExchangeService requestsExchangeService,
            INavigationService navigationService,
            RoomDataStore roomDataStore)
        {
            this._createRoomViewModel = createRoomViewModel;
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
            return !string.IsNullOrWhiteSpace(_createRoomViewModel.RoomName?.Trim())
                   && _createRoomViewModel.MaxPlayers > 0
                   && _createRoomViewModel.QuestionsCount > 0
                   && _createRoomViewModel.QuestionTimeout > 0;
        }

        /// <summary>
        /// Executes the process of creating a room and fetching players.
        /// </summary>
        public override async void Execute(object parameters)
        {
            RoomDataModel? roomData = await CreateRoom();
            this._roomDataStore.CurrentRoomData = roomData;
            if (roomData != null)
            {
                this._navigationService.NavigateTo<RoomAdminViewModel>();
            }

        }


        /// <summary>
        /// Sends a request to create a room with the specified parameters.
        /// </summary>
        private async Task<RoomDataModel?> CreateRoom()
        {
            string trimmedRoomName = _createRoomViewModel.RoomName?.Trim();

            var createRoomRequest = new CreateRoomRequest(
                trimmedRoomName,
                _createRoomViewModel.MaxPlayers,
                _createRoomViewModel.QuestionsCount,
                _createRoomViewModel.QuestionTimeout);

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
                    _createRoomViewModel.QuestionCountError = createRoomResponse.Errors.QuestionCountError;
                }

            }
            else
            {
                _createRoomViewModel.ErrorMessage = "SERVER ERROR: " + responseInfo.ErrorResponse.Message;
            }

            return null; 

        }
    }


}
