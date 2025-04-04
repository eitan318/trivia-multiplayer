#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const vector<char> buffer)
{
    int jsonLength = 0;
    std::memcpy(&jsonLength, buffer.data() + 1, sizeof(int)); //get the size of the packet

    std::string jsonmsg(buffer.begin() + 5, buffer.begin() + 5 + jsonLength);

    nlohmann::json j = nlohmann::json::parse(jsonmsg);

    LoginRequest request;
    request.username = j["username"];
    request.password = j["password"];

    return request;
}
SignupRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(const vector<char> buffer) {
    int jsonLength = 0;
    std::memcpy(&jsonLength, buffer.data() + 1, sizeof(int)); //get the size of the packet

    std::string jsonmsg(buffer.begin() + 5, buffer.begin() + 5 + jsonLength);

    nlohmann::json j = nlohmann::json::parse(jsonmsg);

    SignupRequest request;
    request.email = j["email"];
    request.username = j["username"];
    request.password = j["password"];

    return request;
}