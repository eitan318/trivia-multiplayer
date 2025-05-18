
namespace ClientApp.Models.Requests
{
    /// <summary>
    /// Represents a request to reset a user's password.
    /// </summary>
    class ResetPasswordRequest : IRequest
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="ResetPasswordRequest"/> class.
        /// </summary>
        /// <param name="newPassword">The new password to set for the user.</param>
        /// <param name="email">The username of the user whose password is being reset.</param>
        public ResetPasswordRequest(string newPassword, string email, string tocken)
        {
            this.NewPassword = newPassword;
            this.Email = email;
            ResetPasswordTocken = tocken;
        }

        public RequestsCodes GetCode() => RequestsCodes.ResetPasswordRequest;

        public string Email { get; }

        public string NewPassword { get; }

        public string ResetPasswordTocken { get; }
    }
}
