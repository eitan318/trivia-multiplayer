#pragma once
#include "json.hpp"
#include <string>


struct PlayerResults {
    std::string username;
    unsigned int correctAnswerCount = 0;
    unsigned int wrongAnswerCount = 0;
    double averageAnswerTime = 0.0;

    // Parameterized constructor
    PlayerResults(const std::string& uname, unsigned int correct, unsigned int wrong, double avgTime)
        : username(uname), correctAnswerCount(correct), wrongAnswerCount(wrong), averageAnswerTime(avgTime) {
    }
};




// Define a to_json function for RoomData
inline void to_json(nlohmann::json& j, const PlayerResults& playerResults) {
    j = nlohmann::json{
        {"Username", playerResults.username},
        {"CorrectAnswerCount", playerResults.correctAnswerCount},
        {"WrongAnswerCount", playerResults.wrongAnswerCount},
        {"AverageAnswerTime", playerResults.averageAnswerTime},
    };
}