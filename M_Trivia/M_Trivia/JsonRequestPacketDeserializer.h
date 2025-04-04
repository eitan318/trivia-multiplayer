#pragma once
#include <vector>
#include "Requests.hpp"
#include "json.hpp"

using namespace std;

class JsonRequestPacketDeserializer {
public:
	LoginRequest deserializeLoginRequest(const vector<char> buffer);
	SignupRequest deserializeSignUpRequest(const vector<char> buffer);
};