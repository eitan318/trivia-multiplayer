#include "JsonRequestPacketDeserializer.h"

#define MSG_CODE_SIZE 1


LoginRequest deserializeLoginRequest(const std::vector<char>& buffer)
{
    int jsonLength = 0;
    std::memcpy(&jsonLength, buffer.data() + MSG_CODE_SIZE, sizeof(int)); //get the size of the packet into an int variable

    std::string jsonmsg(buffer.begin() + MSG_CODE_SIZE + sizeof(int), buffer.begin() + MSG_CODE_SIZE + sizeof(int) + jsonLength); //get data as string

    nlohmann::json j = nlohmann::json::parse(jsonmsg); //parse the data to json

    LoginRequest request;
    request.username = j["username"];
    request.password = j["password"];

    return request;
}
SignupRequest deserializeSignUpRequest(const std::vector<char>& buffer) {
    int jsonLength = 0;
    std::memcpy(&jsonLength, buffer.data() + MSG_CODE_SIZE, sizeof(int)); //get the size of the packet

    std::string jsonmsg(buffer.begin() + MSG_CODE_SIZE + sizeof(int), buffer.begin() + MSG_CODE_SIZE + sizeof(int) + jsonLength);

    nlohmann::json j = nlohmann::json::parse(jsonmsg);

    SignupRequest request;
    request.email = j["email"];
    request.username = j["username"];
    request.password = j["password"];

    return request;
}