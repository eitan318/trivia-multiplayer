#include "JsonResponsePacketSerializer.h"
#include "HighScoreInfo.hpp"
#include "RoomData.h"
#include "PersonalStatistics.hpp"

// Define a to_json function for RoomData
void to_json(nlohmann::json& j, const RoomData& roomData) {
    j = nlohmann::json{
        {"id", roomData.id},
        {"name", roomData.name},
        {"maxPlayers", roomData.maxPlayers},
        {"numOfQuestionsInGame", roomData.numOfQuestionsInGame},
        {"timePerQuestion", roomData.timePerQuestion},
        {"status", roomData.status}
    };
}

// Define a to_json function for HighScoreInfo
void to_json(nlohmann::json& j, const HighScoreInfo& highScoreInfo) {
    j = nlohmann::json{
        {"game_name", highScoreInfo.game_name},
        {"player_username", highScoreInfo.username},
        {"totsl_score", highScoreInfo.total_score},
    };
}

// Define a to_json function for PersonalStatistics
void to_json(nlohmann::json& j, const PersonalStatistics& personalStatistics) {
    j = nlohmann::json{
        {"username", personalStatistics.username},
        {"avg_answer_time", personalStatistics.avgAnswerTime},
        {"games_played", personalStatistics.gamesPlayed},
        {"total_answers", personalStatistics.totalAnswers},
        {"total_correct_answers", personalStatistics.totalCorrectAnswers}
    };
}


std::vector<char> JsonResponsePacketSerializer::serializeGeneralResponse(int code, const nlohmann::json& response)
{
    std::vector<char> res;
    res.push_back((char)code);

    std::string json_str = response.dump();

    int json_length = json_str.size();
    res.resize(res.size() + sizeof(int));
    std::memcpy(res.data() + MSG_CODE_SIZE, &json_length, sizeof(int));

    res.insert(res.end(), json_str.begin(), json_str.end());

    return res;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& response)
{
    nlohmann::json json_response;
    json_response["message"] = response.message;
    return serializeGeneralResponse(C_ErrorResponse, json_response);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const SignupResponse& response)
{
    nlohmann::json json_response;
    json_response["status"] = response.status;
    return serializeGeneralResponse(C_SignupResponse, json_response);
}

std::vector<char> JsonResponsePacketSerializer::JsonResponsePacketSerializer::serializeResponse(const LoginResponse& response)
{
    nlohmann::json json_response;
    json_response["status"] = response.status;
    return serializeGeneralResponse(C_LoginResponse, json_response);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const LogoutResponse& response)
{
    nlohmann::json json_response;
    json_response["status"] = response.status;
    return serializeGeneralResponse(C_LogoutResponse, json_response);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const GetRoomsResponse& response)
{
    nlohmann::json json_response;
    json_response["status"] = response.status;
    json_response["rooms"] = response.rooms;

    return serializeGeneralResponse(C_GetRoomsResponse, json_response);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse& response)
{
    nlohmann::json json_response;
    json_response["players"] = response.players;

    return serializeGeneralResponse(C_GetPlayersInRoomResponse, json_response);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const GetHighScoreResponse& response)
{
    nlohmann::json json_response;
    json_response["status"] = response.status;
    json_response["statistics"] = response.statistics;

    return serializeGeneralResponse(C_GetHighScoreResponse, json_response);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const GetPersonalStatsResponse& response)
{
    nlohmann::json json_response;
    json_response["status"] = response.status;
    json_response["statistics"] = response.statistics;

    return serializeGeneralResponse(C_GetPersonalStatsResponse, json_response);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse& response)
{
    nlohmann::json json_response;
    json_response["status"] = response.status;

    return serializeGeneralResponse(C_JoinRoomResponse, json_response);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(const CreateRoomResponse& response)
{
    nlohmann::json json_response;
    json_response["status"] = response.status;

    return serializeGeneralResponse(C_CreateRoomResponse, json_response);
}


