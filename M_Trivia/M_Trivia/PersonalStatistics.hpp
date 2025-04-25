#pragma once
#include <string>
#include "json.hpp"

/**
 * @struct PersonalStatistics
 * @brief Represents the personal statistics of a user in a game, including performance metrics.
 */
struct PersonalStatistics {
    std::string username;      
    int totalCorrectAnswers;   
    int gamesPlayed;           
    int totalAnswers;         
    double avgAnswerTime;      

    /**
     * @brief Constructs a PersonalStatistics object with all member variables initialized.
     * @param user The username of the player.
     * @param totalCorrect Total number of correct answers by the player.
     * @param games Total number of games played by the player.
     * @param totalAns Total number of answers provided by the player.
     * @param avgTime Average time taken to answer, in seconds.
     */
    PersonalStatistics(const std::string& user, int totalCorrect, int games, int totalAns, double avgTime)
        : username(user), totalCorrectAnswers(totalCorrect), gamesPlayed(games),
        totalAnswers(totalAns), avgAnswerTime(avgTime) {
    }
};

/**
 * @brief Serializes a PersonalStatistics object into a JSON representation.
 * @param j The JSON object to populate with serialized data.
 * @param personalStatistics The PersonalStatistics object to serialize.
 */
inline void to_json(nlohmann::json& j, const PersonalStatistics& personalStatistics) {
    j = nlohmann::json{
        {"username", personalStatistics.username},
        {"avg_answer_time", personalStatistics.avgAnswerTime},
        {"games_played", personalStatistics.gamesPlayed},
        {"total_answers", personalStatistics.totalAnswers},
        {"total_correct_answers", personalStatistics.totalCorrectAnswers}
    };
}
