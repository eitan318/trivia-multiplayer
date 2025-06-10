
namespace ClientApp.Models.Requests
{
    class SubmitAnswerRequest : IRequest
    {
        public uint correctAnswerId { get; }
        public SubmitAnswerRequest(uint CorrectAnswerID)
        {
            this.correctAnswerId = CorrectAnswerID;
        }
        public RequestsCodes GetCode() => RequestsCodes.SubmitAnswerRequest;

    }
}
