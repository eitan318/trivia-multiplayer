#pragma once
/**
 * @enum ResponseCodes
 * @brief Enumerates the response codes for different response types.
 */
enum class ResponseCodes : unsigned char {
    C_ErrorResponse = 0,
    C_LoginResponse = 1,
    C_GetRoomsResponse = 2,
    C_GetPlayersInRoomResponse = 3,
    C_GetHighScoreResponse = 4,
    C_GetPersonalStatsResponse = 5,
    C_SendPasswordResetCodeResponse = 6,
    C_SignupResponse = 7,
    C_ResetPasswordResponse = 8,
    C_JoinRoomResponse = 9,
    C_CreateRoomResponse = 10,
    C_LogoutResponse = 11,
    C_HighScoresRespones = 12,
    C_VerifyPasswordResetCodeResponse = 13,
    C_StartGameResponse = 14,
    C_LeaveRoomResponse = 15,
    C_GetRoomStatusResponse = 16,
    C_CloseRoomResponse = 17,
    C_GetQuestionResponse = 18,
    C_LeaveGameResponse = 19,
    C_GetGameResultsResponse = 20,
    C_SubmitAnswerResponse = 21,
    C_GetRoomStateResponse = 22,
    C_GetGameStateResponse = 23,
    C_Leave1v1WaitingListResponse = 24,
    C_DidFound1v1MatchResponse = 25,
    C_Join1v1WaitingListResponse = 26,
    C_Get1v1GameSettingsResponse = 27,
    C_AddQuestionResponse = 28,
};

#define GENERAL_SUCCESS_RESPONSE_STATUS 0