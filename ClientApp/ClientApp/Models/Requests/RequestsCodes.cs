using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientApp.Models.Requests
{
    public enum RequestsCodes
    {
        LoginRequest = 1,
        SignupRequest = 2,
        LogoutRequest = 3,
        GetRoomsRequest = 4,
        HighScoresRequest = 5,
        ForgotPasswordRequest = 6,
        ResetPasswordRequest = 7
    }
}
