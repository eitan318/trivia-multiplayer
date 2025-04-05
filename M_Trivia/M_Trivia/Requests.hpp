#pragma once
#include <string>

enum RequestsCodes {
	C_LoginRequest = 1,
	C_SignupRequest = 2
};

struct LoginRequest {
	std::string username;
	std::string password;
};

struct SignupRequest {
	std::string username;
	std::string password;
	std::string email;
};