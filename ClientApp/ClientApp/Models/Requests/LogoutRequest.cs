
namespace ClientApp.Models.Requests
{
    /// <summary>
    /// Represents a request for logging out
    /// /// </summary>
    class LogoutRequest : IRequest
    {
        public RequestsCodes GetCode() => RequestsCodes.LogoutRequest;
    }
}
