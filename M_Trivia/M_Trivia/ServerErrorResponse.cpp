#include "ServerErrorResponse.hpp"
#include "json.hpp"


ServerErrorResponse::ServerErrorResponse(const std::string& message) : Response((unsigned int)GENERAL_SUCCESS_RESPONSE_STATUS), message(message) {

}


nlohmann::json ServerErrorResponse::getJson() const {
    nlohmann::json j = Response::getJson();
    j["Message"] = message; 
    return j;
}


