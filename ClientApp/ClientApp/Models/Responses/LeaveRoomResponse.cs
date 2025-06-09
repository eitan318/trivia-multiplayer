namespace ClientApp.Models.Responses
{
    class LeaveRoomResponse : Response
    {
        private LeaveRoomResponse() { }
        public override ResponsesCodes GetCode() => ResponsesCodes.LeaveRoomResponse;
    }
}
