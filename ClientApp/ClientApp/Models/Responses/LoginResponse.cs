using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;

namespace ClientApp.Models.Responses
{
    class LoginResponse : Response
    {
        private LoginResponse() { }
        [JsonProperty]
        public LoginResponseErrors Errors { get; private set; }
        public override ResponsesCodes GetCode() => ResponsesCodes.LoginResponse;
    }
}
