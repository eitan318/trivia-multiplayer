using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.ViewModels;

namespace ClientApp.Commands
{
    class SubmitAnswerCommand : CommandBase
    {
        private readonly RequestsExchangeService _requestsExchangeService;
        private readonly GameAnsweringViewModel _gameViewModel;
        private readonly INavigationService _navigationService;

        public SubmitAnswerCommand(RequestsExchangeService requestsExchangeService,
                                   GameAnsweringViewModel gameViewModel,
                                   INavigationService navigationService)
        {
            _requestsExchangeService = requestsExchangeService;
            _gameViewModel = gameViewModel;
            _navigationService = navigationService;
        }

        public override async void Execute(object parameter)
        {
            if(_gameViewModel.SelectedAnswerIndex != -1)
            {
            SubmitAnswerRequest request = new SubmitAnswerRequest(_gameViewModel.SelectedAnswerIndex);
            ResponseInfo<SubmitAnswerResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<SubmitAnswerResponse>(request);
            if (!responseInfo.NormalResponse)
                return;

            uint currectAnswerId = responseInfo.Response.CorrectAnswerId;

             _navigationService.NavigateTo<WaitingBetweenQuestionsViewModel>();
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
