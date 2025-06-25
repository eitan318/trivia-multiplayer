namespace ClientApp.Models.Requests
{
    class SubmitAnswerRequest : IRequest
    {
        public int ChosenAnswerId { get; }
        public SubmitAnswerRequest(int chosenAnswerId)
        {
            this.ChosenAnswerId = chosenAnswerId;
        }
        public RequestsCodes GetCode() => RequestsCodes.SubmitAnswerRequest;

    }
}
