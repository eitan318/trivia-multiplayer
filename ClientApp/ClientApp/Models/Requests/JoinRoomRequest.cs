
namespace ClientApp.Models.Requests
{
    class JoinRoomRequest : IRequest
    {
        public uint RoomId { get; }
        public JoinRoomRequest (uint roomid)
        {
            RoomId = roomid;
        }
        public RequestsCodes GetCode() => RequestsCodes.JoinRoomRequest;
    }
}
