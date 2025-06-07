
namespace ClientApp.Models.Requests
{
    
    class ForgotPasswordRequest : IRequest
    {
        /// <summary>
        /// creates a request for forgot password attempt
        /// </summary>
        /// <param name="email"></param>
        public ForgotPasswordRequest(string email) {
            this.Email = email;
        }
        public RequestsCodes GetCode() => RequestsCodes.SendPasswordResetCodeRequest;
        public string Email { get; }
    }
}
