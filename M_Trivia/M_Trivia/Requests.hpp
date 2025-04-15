#pragma once
#include "CreateRoomRequest.hpp"
#include "GetPlayersInRoomRequest.hpp"
#include "JoinRoomRequest.hpp"
#include "LoginRequest.hpp"
#include "SignupRequest.hpp"
#include "SendPasswordResetCodeRequest.hpp"
#include "ResetPasswordRequest.hpp"


enum RequestsCodes {
	C_LoginRequest = 1,
	C_SignupRequest = 2,
	C_CreateRoomRequest = 3,
	C_GetPlayersInRoomRequest = 4,
	C_JoinRoomRequest = 5,
	C_SendPasswordResetCodeRequest = 6,
	C_ResetPasswordRequest = 7
};








