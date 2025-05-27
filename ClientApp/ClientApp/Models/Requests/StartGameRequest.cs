
namespace ClientApp.Models.Requests
{
    class StartGameRequest : IRequest
    {
        public RequestsCodes GetCode() => RequestsCodes.StartGameRequest;

    }
}
