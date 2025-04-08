#pragma once
#include <string>
#include "json.hpp"


struct PersonalStatistics {
    std::string username;
    int totalCorrectAnswers;
    int gamesPlayed;
    int totalAnswers;
    double avgAnswerTime;

    // Constructor to initialize all members
    PersonalStatistics(const std::string& user, int totalCorrect, int games, int totalAns, double avgTime)
        : username(user), totalCorrectAnswers(totalCorrect), gamesPlayed(games),
        totalAnswers(totalAns), avgAnswerTime(avgTime) {
    }
};


// Define to_json for PersonalStatistics
inline void to_json(nlohmann::json& j, const PersonalStatistics& personalStatistics) {
    j = nlohmann::json{
        {"username", personalStatistics.username},
        {"avg_answer_time", personalStatistics.avgAnswerTime},
        {"games_played", personalStatistics.gamesPlayed},
        {"total_answers", personalStatistics.totalAnswers},
        {"total_correct_answers", personalStatistics.totalCorrectAnswers}
    };
}