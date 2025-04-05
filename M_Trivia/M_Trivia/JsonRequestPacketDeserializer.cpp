#include "JsonRequestPacketDeserializer.h"


LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const std::vector<char>& buffer)
{
    nlohmann::json j = nlohmann::json::parse(buffer);
    LoginRequest request;
    request.username = j["username"];
    request.password = j["password"];

    return request;
}
SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const std::vector<char>& buffer) {
    nlohmann::json j = nlohmann::json::parse(buffer); 
    SignupRequest request;
    request.email = j["email"];
    request.username = j["username"];
    request.password = j["password"];

    return request;
}
