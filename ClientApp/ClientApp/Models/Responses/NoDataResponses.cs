using ClientApp.Models.ResponseErrors;
using Newtonsoft.Json;

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
    class Leave1v1WaitingListResponse : Response<GeneralResponseErrors> { }
    class Join1v1WaitingListResponse : Response<GeneralResponseErrors> { }

}
