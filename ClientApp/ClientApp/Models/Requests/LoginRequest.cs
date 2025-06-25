namespace ClientApp.Models.Requests
{
    
    class LoginRequest : IRequest
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="LoginRequest"/> struct.
        /// </summary>
        /// <param name="username">The username of the user trying to log in.</param>
        /// <param name="password">The password of the user trying to log in.</param>
        public LoginRequest(string username, string password)
        {
            this.Username = username;
            this.Password = password;
        }

        public RequestsCodes GetCode() => RequestsCodes.LoginRequest;

        public string Username { get; }

        public string Password { get; }
    }
}
