using Newtonsoft.Json;
using System.Threading.Tasks;
using ClientApp.Models.ResponseErrors;

namespace ClientApp.Models.Responses
{
    class PasswordResetCodeResponse : Response
    {
        [JsonConstructor]
        private PasswordResetCodeResponse(uint status, PasswordResetCodeResponseErrors errors, string emailCode, string username) : base(status)
        {
            this.EmailCode = emailCode;
            this.Username = username;
            this.Errors = errors;
        }

        public PasswordResetCodeResponseErrors Errors { get; }
        public string EmailCode { get; }
        public string Username { get; }
    }
}
