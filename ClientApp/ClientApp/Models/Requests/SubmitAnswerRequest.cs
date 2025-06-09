
namespace ClientApp.Models.Requests
{
    class SubmitAnswerRequest : IRequest
    {
        public uint correctAnswerId { get; set; }
        public SubmitAnswerRequest(uint correctAnswerID)
        {
            this.correctAnswerId = correctAnswerID;
        }
        public RequestsCodes GetCode() => RequestsCodes.SubmitAnswerRequest;

    }
}
