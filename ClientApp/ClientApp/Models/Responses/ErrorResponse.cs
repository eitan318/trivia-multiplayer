using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class ErrorResponse : Response
    {
        [JsonConstructor]
        private ErrorResponse(uint status, string message) : base(status)
        {
            Message = message;
        }

        public ResponsesCodes GetCode() => ResponsesCodes.ErrorResponse;
        public string Message { get; }
    }
}
