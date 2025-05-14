#include "PasswordCodeResponse.hpp"

#include "json.hpp"



PasswordCodeResponse::PasswordCodeResponse(
	PasswordCodeResponseErrors* errors,
	unsigned int randomCode,
	const std::string& username
)
: Response(errors), emailCode(randomCode), username(username) 
{
}



ResponseCodes PasswordCodeResponse::getCode() const 
{ 
	return ResponseCodes::C_SendPasswordResetCodeResponse; 
}


nlohmann::json  PasswordCodeResponse::getJson() const {
        nlohmann::json j = Response::getJson();
        j["EmailCode"] = emailCode;
        j["Username"] = username;
        return j;
    }


