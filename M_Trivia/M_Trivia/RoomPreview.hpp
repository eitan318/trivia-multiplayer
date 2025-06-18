#pragma once
#include "json.hpp"
#include "RoomData.hpp"
#include "RoomStatus.h"


struct RoomPreview {
    RoomData roomData;
    unsigned int currPlayersAmount;
    RoomStatus status;
};



// Define a to_json function for RoomData
inline void to_json(nlohmann::json& j, const RoomPreview& roomData) {
    j = nlohmann::json{
        {"RoomData", roomData.roomData},
        {"CurrPlayersAmount", roomData.currPlayersAmount},
        {"Status", roomData.status}
    };
}