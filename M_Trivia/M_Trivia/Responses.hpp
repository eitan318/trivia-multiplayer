#pragma once
#include <string>
#include <vector>
#include "RoomData.h"
#include "HighScoreInfo.hpp"
#include "PersonalStatistics.hpp"

enum ResponsesCodes {
	C_ErrorResponse = 0,
	C_LoginResponse = 1,
	C_SignupResponse = 2,
	C_LogoutResponse = 3,
	C_GetRoomsResponse = 4,
	C_GetPlayersInRoomResponse = 5,
	C_GetHighScoreResponse = 6,
	C_GetPersonalStatsResponse = 7,
	C_JoinRoomResponse = 8,
	C_CreateRoomResponse = 9
};


struct ErrorResponse {
	std::string message;
};

struct LoginResponse {
	unsigned int status;
};

struct SignupResponse {
	unsigned int status;
};

struct LogoutResponse {
	unsigned int status;
};

struct GetRoomsResponse {
	unsigned int status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse {
	std::vector<std::string> players;
};

struct GetHighScoreResponse {
	unsigned int status;
	std::vector<HighScoreInfo> statistics;
};

struct GetPersonalStatsResponse {
	unsigned int status;
	std::vector<PersonalStatistics> statistics;
};

struct JoinRoomResponse {
	unsigned int status;
};

struct CreateRoomResponse {
	unsigned int status;
};