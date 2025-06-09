#pragma once
#include "VerifyPasswordResetCodeRequest.hpp"
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
  GetRoomsRequest = 10,
  PersonalStatisticsRequest = 11,
  VerifyPasswordResetCodeRequest = 12,
  CloseRoomRequest = 13,
  StartGameRequest = 14,
  GetRoomStateRequest = 15,
  LeaveRoomRequest = 16,
  LeaveGameRequest = 17,
  GetQuestionRequest = 18,
  SubmitAnswerRequest = 19,
  GetGameResultRequest = 20,
};
