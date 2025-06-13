#pragma once
#include <string>
#include "json.hpp"
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>


inline std::string timeStr(time_t time);


/**
 * @struct HighScoreInfo
 * @brief A structure that holds information about a player's high score in a specific game.
 */
struct HighScoreInfo {
    std::string username; 
    std::string roomName; 
    time_t startTime;
    int totalScore;      
    unsigned int gameId;    
    unsigned int rank;
};

/**
 * @brief Converts a HighScoreInfo object into a JSON object.
 *
 * This function serializes the provided `HighScoreInfo` struct into a JSON object.
 * @param j The JSON object to which the data will be written.
 * @param highScoreInfo The HighScoreInfo object that contains the data to be serialized.
 */
inline void to_json(nlohmann::json& j, const HighScoreInfo& highScoreInfo) {
    j = nlohmann::json{
        {"RoomName", highScoreInfo.roomName},
        {"StartTime", timeStr(highScoreInfo.startTime)},
        {"PlayerUsername", highScoreInfo.username},
        {"TotalScore", highScoreInfo.totalScore},
        {"GameId", highScoreInfo.gameId},
        {"Rank", highScoreInfo.rank}
    };
}

inline std::string timeStr(time_t time) {
    // Convert time_t to tm structure
    struct tm timeInfo;
    localtime_s(&timeInfo, &time);

    // Create a string stream to format the time
    std::ostringstream oss;
    oss << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S"); // ISO 8601 format

    return oss.str();
}
