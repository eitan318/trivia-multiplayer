#include "JsonResponsePacketSerializer.h"

std::vector<char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse)
{

}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(SignupResponse)
{
    return std::vector<char>();
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LoginResponse)
{
    return std::vector<char>();
}
