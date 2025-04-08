#pragma once
#include <string>

struct PlayerStatistics {
    std::string username;
    int totalCurrectAnswers;
    int gamesPlayed;
    int totalAnswers;
    double avgAnswerTime;

    // Constructor to initialize all members
    PlayerStatistics(const std::string& user, int totalCorrect, int games, int totalAns, double avgTime)
        : username(user), totalCurrectAnswers(totalCorrect), gamesPlayed(games),
        totalAnswers(totalAns), avgAnswerTime(avgTime) {
    }
};