
namespace ClientApp.Models.Requests {

class VerifyPasswordResetCodeRequest : IRequest {
  public VerifyPasswordResetCodeRequest(string passwordResetCode) {
    this.PasswordResetCode = passwordResetCode;
  }
  public RequestsCodes GetCode() => RequestsCodes.VerifyPasswordCodeRequest;
  public string PasswordResetCode { get; }
}
}
