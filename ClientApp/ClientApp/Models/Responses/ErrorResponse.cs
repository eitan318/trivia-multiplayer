using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class ErrorResponse : Response<NoResponseErrors>
    {
        private ErrorResponse() { }
        public ErrorResponse(string message) {
            this.Message = message;

        }
        [JsonProperty]
        public string Message { get; private set; }
    }
}
