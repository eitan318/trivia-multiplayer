#pragma once
#include <vector>
#include "Responses.hpp"
#include "json.hpp"


#define MSG_CODE_SIZE 1

class JsonResponsePacketSerializer
{
public:
	static std::vector<char> serializeResponse(const ErrorResponse&);
	static std::vector<char> serializeResponse(const SignupResponse&);
	static std::vector<char> serializeResponse(const LoginResponse&);
};

