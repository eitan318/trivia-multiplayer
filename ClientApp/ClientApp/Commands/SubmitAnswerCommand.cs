using ClientApp.Models.Requests;
using ClientApp.Models.Responses;
using ClientApp.Services;
using ClientApp.ViewModels;

namespace ClientApp.Commands
{
    public class SubmitAnswerCommand : CommandBase
    {
        private readonly RequestsExchangeService _requestsExchangeService;
        private readonly INavigationService _navigationService;

        public SubmitAnswerCommand(RequestsExchangeService requestsExchangeService,
                                   INavigationService navigationService)
        {
            _requestsExchangeService = requestsExchangeService;
            _navigationService = navigationService;
        }

        public override async void Execute(object parameter)
        {
            if (parameter is not GameAnsweringViewModel gameAnsweringViewModel)
            {
                return;
            }

            if(gameAnsweringViewModel.SelectedAnswerIndex != -1)
            {
            SubmitAnswerRequest request = new SubmitAnswerRequest(gameAnsweringViewModel.SelectedAnswerIndex);
            ResponseInfo<SubmitAnswerResponse> responseInfo = await _requestsExchangeService.ExchangeRequest<SubmitAnswerResponse>(request);
            if (!responseInfo.NormalResponse)
                return;

            uint currectAnswerId = responseInfo.Response.CorrectAnswerId;

             _navigationService.NavigateTo<WaitingBetweenQuestionsViewModel>();
            }
        }

        public override bool CanExecute(object parameter)
        {
            if (parameter is not GameAnsweringViewModel gameAnsweringViewModel)
            {
                return false;
            }
            return gameAnsweringViewModel.SelectedAnswerIndex >= 0;
        }

        public void RaiseCanExecuteChanged()
        {
            base.RaiseCanExecuteChanged();
        }
    }
}
