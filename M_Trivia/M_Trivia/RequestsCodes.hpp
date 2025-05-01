#pragma once
enum class RequestCodes : unsigned char {
    LoginRequest = 1,
    SignupRequest = 2,
    LogoutRequest = 3,
    CreateRoomRequest = 4,
    GetPlayersInRoomRequest = 5,
    JoinRoomRequest = 6,
    SendPasswordResetCodeRequest = 7,
    ResetPasswordRequest = 8,
    GetHighScoresRequest = 9,
    GetRoomsRequest = 10
};








