
namespace ClientApp.Models.Requests
{
    
    class SignupRequest : IRequest
    {
        public SignupRequest(string username, string password, 
            string email, string phoneNumber, string houseAddress, string birthDate) {

            this.UserRecord = new UserRecord(username, password,
            email, phoneNumber, houseAddress, birthDate);
        }
        public RequestsCodes GetCode() => RequestsCodes.SignupRequest;
        public UserRecord UserRecord { get; }
    }
}
