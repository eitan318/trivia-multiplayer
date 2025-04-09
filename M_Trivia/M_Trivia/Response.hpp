#pragma once 
#include "json.hpp"

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


class Response {
public:
	virtual unsigned int getCode() const = 0;
	virtual  nlohmann::json getJson() const = 0;
};