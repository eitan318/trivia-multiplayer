#pragma once
#include <vector>
#include "Responses.hpp"
#include "json.hpp"

class JsonResponsePacketSerializer
{
public:
	std::vector<char> serializeResponse(const ErrorResponse&);
	std::vector<char> serializeResponse(const SignupResponse&);
	std::vector<char> serializeResponse(const LoginResponse&);
};

