using ClientApp.Models.ResponseErrors;

namespace ClientApp.Models.Responses
{
    class LeaveRoomResponse : Response<NoResponseErrors> { }
    class LeaveGameResponse : Response<NoResponseErrors> { }
    class LoginResponse : Response<LoginResponseErrors> { }
    class LogoutResponse : Response<NoResponseErrors> { }
    class PasswordResetCodeResponse : Response<PasswordResetCodeResponseErrors> { }
    class ResetPasswordResponse : Response<ResetPasswordResponseErrors> { }
    class JoinRoomResponse : Response<GeneralResponseErrors> { }
    class SignupResponse : Response<SignupResponseErrors> { }
    class StartGameResponse : Response<GeneralResponseErrors> { }
}
