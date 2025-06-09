
using ClientApp.Models.ResponseErrors;

namespace ClientApp.Models.Responses
{
    class LeaveGameResponse : Response
    {
        private LeaveGameResponse() { }
        public GeneralResponseErrors Errors { get; private set; }
        public override ResponsesCodes GetCode() => ResponsesCodes.LeaveGameResponse;
    }
}
