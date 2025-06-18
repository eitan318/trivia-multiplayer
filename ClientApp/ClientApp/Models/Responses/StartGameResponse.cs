
using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class StartGameResponse : Response
    {
        private StartGameResponse() { }
        
        [JsonProperty]
        public StartGameResponseErrors Errors { get; private set; }
        public ResponsesCodes GetCode() => ResponsesCodes.StartGameResponse;
    }
}
