#include "ServerErrorResponse.hpp"
#define GENERALERROR 0
#include "json.hpp"


ServerErrorResponse::ServerErrorResponse(const std::string& message) : Response((unsigned int)(GENERALERROR)), message(message) {

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


