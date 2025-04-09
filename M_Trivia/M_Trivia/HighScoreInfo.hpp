#pragma once
#include <string>
#include "json.hpp"

struct HighScoreInfo {
	std::string username;
	std::string game_name;
	int total_score;
	int game_id;
};


// Define a to_json function for HighScoreInfo
inline void to_json(nlohmann::json& j, const HighScoreInfo& highScoreInfo) {
    j = nlohmann::json{
        {"game_name", highScoreInfo.game_name},
        {"player_username", highScoreInfo.username},
        {"totsl_score", highScoreInfo.total_score},
    };
}