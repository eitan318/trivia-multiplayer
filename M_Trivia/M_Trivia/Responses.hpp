#include <string>

enum CODES {
	C_LoginResponse = 1,
	C_SignupResponse = 2,
	C_ErrorResponse = 5
};

struct LoginResponse {
	unsigned int status;
};

struct SignupResponse {
	unsigned int status;
};

struct ErrorResponse {
	std::string message;
};