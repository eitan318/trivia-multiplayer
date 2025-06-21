#pragma once
#include "json.hpp"
#include <string>


struct PlayerResults {
    std::string username;
    unsigned int correctAnswerCount = 0;
    unsigned int wrongAnswerCount = 0;
    unsigned int notAnsweredCount = 0;
    int score = 0;
    double averageAnswerTime = 0.0;

    // Parameterized constructor
    PlayerResults(const std::string& uname, unsigned int correct, unsigned int wrong, 
        int score, double avgTime, unsigned int questionAmount)
        : username(uname), correctAnswerCount(correct), wrongAnswerCount(wrong),
        averageAnswerTime(avgTime), notAnsweredCount(questionAmount - correctAnswerCount - wrongAnswerCount), score(score) {
    }
};


// Define a to_json function for RoomData
inline void to_json(nlohmann::json& j, const PlayerResults& playerResults) {
    j = nlohmann::json{
        {"Username", playerResults.username},
        {"CorrectAnswerCount", playerResults.correctAnswerCount},
        {"WrongAnswerCount", playerResults.wrongAnswerCount},
        {"NotAnsweredCount", playerResults.notAnsweredCount},
        {"Score", playerResults.score},
        {"AverageAnswerTime", playerResults.averageAnswerTime},
    };
}