using Newtonsoft.Json;
using ClientApp.Models.ResponseErrors;

namespace ClientApp.Models.Responses
{
    class PasswordResetCodeResponse : Response
    {
        private PasswordResetCodeResponse() { }
        [JsonProperty]
        public PasswordResetCodeResponseErrors Errors { get; private set; }
    }
}
