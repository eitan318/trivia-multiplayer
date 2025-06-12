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
    class SubmitAnswerCommand : CommandBase
    {
        private readonly RequestsExchangeService _requestsExchangeService;
        private readonly GameViewModel _gameViewModel;
        private readonly RoomDataStore _roomDataStore;
        private readonly INavigationService _navigationService;
        public SubmitAnswerCommand(
            RequestsExchangeService requestsExchangeService,
            GameViewModel gameViewModel,
            RoomDataStore roomDataStore,
            INavigationService navigationService
            ) {
            this._requestsExchangeService = requestsExchangeService;
            this._gameViewModel = gameViewModel;
            this._roomDataStore = roomDataStore;
            this._navigationService = navigationService;
        }
        public override async void Execute(object parameter)
        {
            _gameViewModel.Timer.Pause();

            // Prepare the login request and send it
            SubmitAnswerRequest submitAnswerRequests = new SubmitAnswerRequest(_gameViewModel.SelectedAnswerIndex);
            ResponseInfo<SubmitAnswerResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<SubmitAnswerResponse>(submitAnswerRequests);
            if (responseInfo.NormalResponse)
            {
                SubmitAnswerResponse submitAnswerResponse = responseInfo.Response;
                if(submitAnswerResponse.Status == 0)
                {
                    _gameViewModel.Score += submitAnswerResponse.AnswerScore;
                }
                else
                {
                }

            }

            if (_gameViewModel.QuestionNumber == _gameViewModel.TotalQuestions) 
            {
                _navigationService.NavigateTo<MenuViewModel>();
            }

            _gameViewModel.NextQuestion();

              
        }

        public override bool CanExecute(object parameter)
        {
            return _gameViewModel.SelectedAnswerIndex >= 0;
        }

        public void RaiseCanExecuteChanged()
        {
            base.RaiseCanExecuteChanged();
        }





    }
}
