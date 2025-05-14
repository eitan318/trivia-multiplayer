#include "ServerErrorResponse.hpp"

#include "json.hpp"


ServerErrorResponse::ServerErrorResponse(const std::string& message) : Response((unsigned int)(0)), message(message) {

}


ResponseCodes ServerErrorResponse::getCode() const 
{
	return ResponseCodes::C_ErrorResponse; 
}



nlohmann::json ServerErrorResponse::getJson() const {
    nlohmann::json j = Response::getJson();
    j["Message"] = message; 
    return j;
}


