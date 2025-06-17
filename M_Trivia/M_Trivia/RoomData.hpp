#pragma once
#include "json.hpp"
#include <string>

struct RoomData {
    unsigned int id;
    std::string name;
    unsigned int maxPlayers;
    unsigned int numOfQuestionsInGame;
    double timePerQuestion;
    double scoreShowingTime;
};

// Define a to_json function for RoomData
inline void to_json(nlohmann::json& j, const RoomData& roomData) {
    j = nlohmann::json{
        {"Id", roomData.id},
        {"RoomName", roomData.name},
        {"MaxPlayers", roomData.maxPlayers},
        {"NumOfQuestionsInGame", roomData.numOfQuestionsInGame},
        {"TimePerQuestion", roomData.timePerQuestion},
        {"ScoreShowingTime", roomData.scoreShowingTime},
    };
}

// Define a from_json function for RoomData
inline void from_json(const nlohmann::json& j, RoomData& roomData) {
    j.at("Id").get_to(roomData.id);
    j.at("RoomName").get_to(roomData.name);
    j.at("MaxPlayers").get_to(roomData.maxPlayers);
    j.at("NumOfQuestionsInGame").get_to(roomData.numOfQuestionsInGame);
    j.at("TimePerQuestion").get_to(roomData.timePerQuestion);
    j.at("ScoreShowingTime").get_to(roomData.scoreShowingTime);
}
