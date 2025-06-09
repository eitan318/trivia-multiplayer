using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class ResetPasswordResponse : Response
    {
        private ResetPasswordResponse() { }
        [JsonProperty]
        public ResetPasswordErrors Errors { get; private set; }
        public override ResponsesCodes GetCode() => ResponsesCodes.ResetPasswordResponse;
    }
}
