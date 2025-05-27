namespace ClientApp.Models.Requests
{
    enum RequestsCodes
    {
        LoginRequest = 1,
        SignupRequest = 2,
        LogoutRequest = 3,
        CreateRoomRequest = 4,
        GetPlayersInRoomRequest = 5,
        JoinRoomRequest = 6,
        SendPasswordResetCodeRequest = 7,
        ResetPasswordRequest = 8,
        GetHighScoresRequest = 9,
        GetRoomsRequest = 10,
        PersonalStatisticsRequest = 11,
        VerifyPasswordCodeRequest = 12,
        CloseRoomRequest = 13,
        StartGameRequest = 14,
        GetRoomStateRequest = 15,
        LeaveRoomRequest = 16, 

    }
}