
namespace ClientApp.Models.Requests {
/// <summary>
/// Represents a request for verifing a password reset code request
/// /// </summary>
class VerifyPasswordResetCodeRequest : IRequest {
  public VerifyPasswordResetCodeRequest(string passwordResetCode) {
    this.PasswordResetCode = passwordResetCode;
  }
  public RequestsCodes GetCode() => RequestsCodes.VerifyPasswordCodeRequest;
  public string PasswordResetCode { get; }
}
}
