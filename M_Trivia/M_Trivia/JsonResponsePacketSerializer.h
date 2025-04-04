#pragma once
#include <vector>
#include "Responses.hpp"

class JsonResponsePacketSerializer
{
public:
	std::vector<char> serializeResponse(ErrorResponse);
	std::vector<char> serializeResponse(SignupResponse);
	std::vector<char> serializeResponse(LoginResponse);
};

