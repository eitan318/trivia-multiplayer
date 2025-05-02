using Newtonsoft.Json;
using System.Threading.Tasks;
using ClientApp.Models.ResponseErrors;

namespace ClientApp.Models.Responses
{
    class PasswordResetCodeResponse : Response
    {
        private PasswordResetCodeResponse() { }
        [JsonProperty]
        public PasswordResetCodeResponseErrors Errors { get; private set; }
        [JsonProperty]
        public string EmailCode { get; private set; }
        [JsonProperty]
        public string Username { get; private set; }
    }
}
