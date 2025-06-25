namespace ClientApp.Models.Requests
{
    class LeaveRoomRequest : IRequest
    {
        public RequestsCodes GetCode() => RequestsCodes.LeaveRoomRequest;

    }
}
