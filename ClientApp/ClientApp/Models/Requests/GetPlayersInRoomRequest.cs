
namespace ClientApp.Models.Requests
{
    /// <summary>
    /// Represents a request for getting players in room
    /// /// </summary>
    class GetPlayersInRoomRequest : IRequest
    {
        public uint RoomId { get; }

        public GetPlayersInRoomRequest(uint roomId)
        {
            this.RoomId = roomId;
        }
        public RequestsCodes GetCode() => RequestsCodes.GetPlayersInRoomRequest;
    }
}
