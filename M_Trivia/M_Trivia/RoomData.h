#pragma once
#include <iostream>
#include "json.hpp"


struct RoomData {
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	bool status;
};



// Define a to_json function for RoomData
inline void to_json(nlohmann::json& j, const RoomData& roomData) {
    j = nlohmann::json{
        {"id", roomData.id},
        {"name", roomData.name},
        {"maxPlayers", roomData.maxPlayers},
        {"numOfQuestionsInGame", roomData.numOfQuestionsInGame},
        {"timePerQuestion", roomData.timePerQuestion},
        {"status", roomData.status}
    };
}