using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class GetRoomStateResponse : Response
    {
        private GetRoomStateResponse() { }


        [JsonProperty]
        public bool HasGameBegun { get; private set; }

        [JsonProperty]
        public uint AnswerCount { get; private set; }

        [JsonProperty]
        public double AnswerTimeOut { get; private set; }

        [JsonProperty]
        public List<LoggedUser> Players { get; private set; }
    }
}
