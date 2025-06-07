#include "LogoutResponse.hpp"
#include "json.hpp"



LogoutResponse::LogoutResponse(unsigned int status) : Response(status) {

}

ResponseCodes LogoutResponse::getCode() const 
{
	return ResponseCodes::C_LogoutResponse; 
}

