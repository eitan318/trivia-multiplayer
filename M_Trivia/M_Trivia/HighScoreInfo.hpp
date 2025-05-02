#pragma once
#include <string>
#include "json.hpp"

/**
 * @struct HighScoreInfo
 * @brief A structure that holds information about a player's high score in a specific game.
 */
struct HighScoreInfo {
    std::string UserName; 
    std::string GameName; 
    int TotalScore;      
    int GameId;           
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
        {"GameName", highScoreInfo.GameName},  
        {"PlayerUsername", highScoreInfo.UserName},
        {"TotalScore", highScoreInfo.TotalScore},
        {"GameId", highScoreInfo.GameId},
    };
}
