#include "JsonResponsePacketSerializer.h"

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& errorResponse)
{
    std::vector<char> res;
    res.push_back((char)C_ErrorResponse); 

    nlohmann::json json_response;
    json_response["message"] = errorResponse.message;
    std::string json_str = json_response.dump();

    int json_length = json_str.size();
    res.resize(res.size() + sizeof(int));
    std::memcpy(res.data() + MSG_CODE_SIZE, &json_length, sizeof(int));

    res.insert(res.end(), json_str.begin(), json_str.end());

    return res;
}



std::vector<char> JsonResponsePacketSerializer::serializeResponse(const SignupResponse& signupResponse)
{
    std::vector<char> res;
    res.push_back((char)C_SignupResponse);

    nlohmann::json json_response;
    json_response["status"] = signupResponse.status;
    std::string json_str = json_response.dump();

    int json_length = json_str.size();
    res.resize(res.size() + sizeof(int));
    std::memcpy(res.data() + MSG_CODE_SIZE, &json_length, sizeof(int));

    res.insert(res.end(), json_str.begin(), json_str.end());

    return res;
}

std::vector<char> JsonResponsePacketSerializer::JsonResponsePacketSerializer::serializeResponse(const LoginResponse& loginResponse)
{
    std::vector<char> res;
    res.push_back((char)C_LoginResponse);

    nlohmann::json json_response;
    json_response["status"] = loginResponse.status;
    std::string json_str = json_response.dump();

    int json_length = json_str.size();
    res.resize(res.size() + sizeof(int));
    std::memcpy(res.data() + MSG_CODE_SIZE, &json_length, sizeof(int));

    res.insert(res.end(), json_str.begin(), json_str.end());

    return res;
}
