using System;

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
        /// <param name="username">The username of the user whose password is being reset.</param>
        public ResetPasswordRequest(string newPassword, string username)
        {
            this.NewPassword = newPassword;
            this.Username = username;
        }

        public RequestsCodes GetCode() => RequestsCodes.ResetPasswordRequest;

        public string Username { get; }

        public string NewPassword { get; }
    }
}
