using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.ViewModels;

namespace ClientApp.Commands
{
    class SubmitAnswerCommand : CommandBase
    {
        private readonly RequestsExchangeService _requestsExchangeService;
        private readonly GameViewModel _gameViewModel;
        private readonly INavigationService _navigationService;

        public SubmitAnswerCommand(RequestsExchangeService requestsExchangeService,
                                   GameViewModel gameViewModel,
                                   INavigationService navigationService)
        {
            _requestsExchangeService = requestsExchangeService;
            _gameViewModel = gameViewModel;
            _navigationService = navigationService;
        }

        public override async void Execute(object parameter)
        {
            _gameViewModel.Timer.Stop();

            SubmitAnswerRequest request = new SubmitAnswerRequest(_gameViewModel.SelectedAnswerIndex);
            ResponseInfo<SubmitAnswerResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<SubmitAnswerResponse>(request);

            if (responseInfo.NormalResponse && responseInfo.Response?.Status == 0)
            {
                _gameViewModel.Score += responseInfo.Response.AnswerScore;
            }

            if (_gameViewModel.QuestionNumber == _gameViewModel.TotalQuestions)
            {
                _navigationService.NavigateTo<MenuViewModel>();
            }
            else
            {
                await _gameViewModel.NextQuestion();
            }
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
