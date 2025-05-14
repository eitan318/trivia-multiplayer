#include "LoginResponse.hpp"
#include "json.hpp"


LoginResponse::LoginResponse(LoginResponseErrors* errors)
		: Response(errors)
{
}

ResponseCodes LoginResponse::getCode() const 
{
	return ResponseCodes::C_LoginResponse; 
}
	
