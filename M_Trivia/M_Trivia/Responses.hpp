#include <string>

enum CODES {
	C_LoginResponse,
	C_SignupResponse,
	C_ErrorResponse
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