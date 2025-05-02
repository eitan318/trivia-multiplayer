using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class ErrorResponse : Response
    {
        private ErrorResponse() { }
        public ResponsesCodes GetCode() => ResponsesCodes.ErrorResponse;
        [JsonProperty]
        public string Message { get; private set; }
    }
}
