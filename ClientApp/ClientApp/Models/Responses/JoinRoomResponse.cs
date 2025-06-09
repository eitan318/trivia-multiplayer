using Newtonsoft.Json;
using ClientApp.Models.ResponseErrors;

namespace ClientApp.Models.Responses
{
    class JoinRoomResponse : Response
    {
        private JoinRoomResponse() { }
        public override ResponsesCodes GetCode() => ResponsesCodes.JoinRoomResponse;
        [JsonProperty]
        public JoinRoomResponseErrors Errors { get; private set; }

    }
}
