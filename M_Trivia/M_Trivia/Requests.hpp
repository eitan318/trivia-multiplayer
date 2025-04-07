#pragma once
#include <string>
#include "UserRecord.hpp"

enum RequestsCodes {
	C_LoginRequest = 1,
	C_SignupRequest = 2
};

struct LoginRequest {
	std::string username;
	std::string password;
};

struct SignupRequest {
	UserRecord userRecord;
};