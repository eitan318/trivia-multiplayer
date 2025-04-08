#pragma once
#include <string>

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