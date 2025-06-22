#pragma once
#include "json.hpp"
#include "RoomData.hpp"
#include "RoomStatus.h"
#include "LoggedUser.hpp"


struct RoomPreview {
    RoomPreview(const RoomData& roomData, unsigned int currPlayersAmount, RoomStatus status, const LoggedUser& admin) : 
    roomData(roomData), currPlayersAmount(currPlayersAmount), status(status), admin(admin){
    }

    bool gameStarted() const
    {
        return status == RoomStatus::StartingGame;
    }

    void close() {
        status = RoomStatus::Closing;
    }

    void startGame() {
        status = RoomStatus::StartingGame;
    }

    void enterGame() {
        status = RoomStatus::InGame;
    }

    void closeGame() {
        if (status != Closing) {
            status = RoomStatus::NotInGame;
        }
    }

    const RoomData roomData;
    unsigned int currPlayersAmount;
    RoomStatus status;
    LoggedUser admin;
};



// Define a to_json function for RoomData
inline void to_json(nlohmann::json& j, const RoomPreview& roomData) {
    j = nlohmann::json{
        {"RoomData", roomData.roomData},
        {"CurrPlayersAmount", roomData.currPlayersAmount},
        {"Status", roomData.status},
        {"Admin", roomData.admin}
    };
}