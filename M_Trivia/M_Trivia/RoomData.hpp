#pragma once
#include "json.hpp"
#include <string>


struct RoomData {
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
};



// Define a to_json function for RoomData
inline void to_json(nlohmann::json& j, const RoomData& roomData) {
    j = nlohmann::json{
        {"Id", roomData.id},
        {"RoomName", roomData.name},
        {"MaxPlayers", roomData.maxPlayers},
        {"NumOfQuestionsInGame", roomData.numOfQuestionsInGame},
        {"TimePerQuestion", roomData.timePerQuestion},
    };
}