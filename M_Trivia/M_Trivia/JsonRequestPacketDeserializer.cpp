#include "JsonRequestPacketDeserializer.h"

#define DATASIZE 1


LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const vector<char>& buffer)
{
    int jsonLength = 0;
    std::memcpy(&jsonLength, buffer.data() + DATASIZE, sizeof(int)); //get the size of the packet into an int variable

    std::string jsonmsg(buffer.begin() + DATASIZE + sizeof(int), buffer.begin() + DATASIZE + sizeof(int) + jsonLength); //get data as string

    nlohmann::json j = nlohmann::json::parse(jsonmsg); //parse the data to json

    LoginRequest request;
    //putting data in the login request variable
    request.username = j["username"];
    request.password = j["password"];

    return request;
}
SignupRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(const vector<char>& buffer) {
    int jsonLength = 0;
    std::memcpy(&jsonLength, buffer.data() + DATASIZE, sizeof(int)); //get the size of the packet

    std::string jsonmsg(buffer.begin() + DATASIZE + sizeof(int), buffer.begin() + DATASIZE + sizeof(int) + jsonLength);

    nlohmann::json j = nlohmann::json::parse(jsonmsg);

    SignupRequest request;
    //putting data in the login request variable
    request.email = j["email"];
    request.username = j["username"];
    request.password = j["password"];

    return request;
}