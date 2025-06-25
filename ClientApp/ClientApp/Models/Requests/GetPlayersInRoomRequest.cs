namespace ClientApp.Models.Requests
{
    
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
