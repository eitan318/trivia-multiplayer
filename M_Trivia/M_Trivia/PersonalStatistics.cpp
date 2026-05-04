#include "PersonalStatistics.hpp"

PersonalStatistics::PersonalStatistics(const std::string& user, int totalCorrect, int games, int totalAns, double avgTime)
    : username(user), totalCorrectAnswers(totalCorrect), gamesPlayed(games),
    totalAnswers(totalAns), avgAnswerTime(avgTime) {
}



