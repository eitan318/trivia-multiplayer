#pragma once
#include <string>
#include "json.hpp"

/**
 * @struct HighScoreInfo
 * @brief A structure that holds information about a player's high score in a specific game.
 */
struct HighScoreInfo {
    std::string username; 
    std::string game_name; 
    int total_score;      
    int game_id;           
};

/**
 * @brief Converts a HighScoreInfo object into a JSON object.
 *
 * This function serializes the provided `HighScoreInfo` struct into a JSON object.
 * The fields in the struct are mapped to the respective JSON keys:
 * - "game_name" `highScoreInfo.game_name`
 * - "player_username"  `highScoreInfo.username`
 * - "total_score"  `highScoreInfo.total_score`
 *
 * @param j The JSON object to which the data will be written.
 * @param highScoreInfo The HighScoreInfo object that contains the data to be serialized.
 */
inline void to_json(nlohmann::json& j, const HighScoreInfo& highScoreInfo) {
    j = nlohmann::json{
        {"game_name", highScoreInfo.game_name},  
        {"player_username", highScoreInfo.username},   
        {"total_score", highScoreInfo.total_score},
    };
}
