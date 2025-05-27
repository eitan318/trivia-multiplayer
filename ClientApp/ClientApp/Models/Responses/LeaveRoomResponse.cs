namespace ClientApp.Models.Responses
{
    class LeaveRoomResponse : Response
    {
        private LeaveRoomResponse() { }
        public ResponsesCodes GetCode() => ResponsesCodes.LeaveRoomResponse;
    }
}
