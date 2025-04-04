#pragma once
#include <vector>
#include "Requests.hpp"
#include "json.hpp"

#define MSG_CODE_SIZE 1

class JsonRequestPacketDeserializer {
public:
	static LoginRequest deserializeLoginRequest(const std::vector<char>& buffer);
	static SignupRequest deserializeSignUpRequest(const std::vector<char>& buffer);
};