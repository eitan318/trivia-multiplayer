
namespace ClientApp.Models.Requests
{
    class LeaveGameRequest : IRequest
    {
        public RequestsCodes GetCode() => RequestsCodes.LeaveGameRequest;

    }
}
