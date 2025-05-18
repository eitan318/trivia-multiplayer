
namespace ClientApp.Models.Requests
{
    /// <summary>
    /// Represents a request for getting data of all rooms
    /// /// /// </summary>
    class GetRoomsRequest : IRequest
    {
        public RequestsCodes GetCode() => RequestsCodes.GetRoomsRequest;
    }
}
