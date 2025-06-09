#pragma once
#include "json.hpp"
#include <string>


struct PlayerResults {
    std::string username;
    unsigned int correctAnswerCount;
    unsigned int wrongAnswerCount;
    double averageAnswerTime;
};



// Define a to_json function for RoomData
inline void to_json(nlohmann::json& j, const PlayerResults& playerResults) {
    j = nlohmann::json{
        {"Username", playerResults.username},
        {"CorrectAnswerCount", playerResults.correctAnswerCount},
        {"WrongAnswerCount", playerResults.wrongAnswerCount},
        {"averageAnswerTime", playerResults.averageAnswerTime},
    };
}