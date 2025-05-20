
namespace ClientApp.Models.Requests
{
    class GetRoomsRequest : IRequest
    {
        public RequestsCodes GetCode() => RequestsCodes.GetRoomsRequest;
    }
}
