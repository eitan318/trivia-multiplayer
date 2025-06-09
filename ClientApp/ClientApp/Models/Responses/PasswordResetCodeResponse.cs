using Newtonsoft.Json;
using ClientApp.Models.ResponseErrors;

namespace ClientApp.Models.Responses
{
    class PasswordResetCodeResponse : Response
    {
        private PasswordResetCodeResponse() { }

        public override ResponsesCodes GetCode() => ResponsesCodes.SendPasswordResetCodeResponse;

        [JsonProperty]
        public PasswordResetCodeResponseErrors Errors { get; private set; }
    }
}
