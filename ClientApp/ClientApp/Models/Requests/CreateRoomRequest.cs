
namespace ClientApp.Models.Requests
{
    
    class CreateRoomRequest : IRequest
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="CreateRoomRequest"/> class.
        /// </summary>
        public CreateRoomRequest(RoomDataModel roomData)
        {
            this.RoomData = roomData;
        }

        public RequestsCodes GetCode() => RequestsCodes.CreateRoomRequest;

        public RoomDataModel RoomData { get; }
    }
}
