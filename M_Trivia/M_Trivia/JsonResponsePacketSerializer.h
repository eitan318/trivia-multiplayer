#pragma once
#include <vector>
#include "Responses.hpp"
#include "json.hpp"


#define MSG_CODE_SIZE 1

class JsonResponsePacketSerializer
{
private:
	static std::vector<char> serializeGeneralResponse(int code, const nlohmann::json& response);
public:	
	static std::vector<char> serializeResponse(const ErrorResponse&);
	static std::vector<char> serializeResponse(const SignupResponse&);
	static std::vector<char> serializeResponse(const LoginResponse&);
	static std::vector<char> serializeResponse(const LogoutResponse&);
	static std::vector<char> serializeResponse(const GetRoomsResponse&);
	static std::vector<char> serializeResponse(const GetPlayersInRoomResponse&);
	static std::vector<char> serializeResponse(const GetHighScoreResponse&);
	static std::vector<char> serializeResponse(const GetPersonalStatsResponse&);
	static std::vector<char> serializeResponse(const JoinRoomResponse&);
	static std::vector<char> serializeResponse(const CreateRoomResponse&);
};

