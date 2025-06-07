
namespace ClientApp.Models.Requests
{
    
    class LogoutRequest : IRequest
    {
        public RequestsCodes GetCode() => RequestsCodes.LogoutRequest;
    }
}
