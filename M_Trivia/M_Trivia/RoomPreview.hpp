#pragma once
#include "json.hpp"
#include "RoomData.hpp"
#include "RoomStatus.h"
#include "LoggedUser.hpp"

/**
 * @struct RoomPreview
 * @brief Represents a preview of a room with metadata and status.
 */
struct RoomPreview {
    /**
     * @brief Constructs a RoomPreview from RoomData and other attributes.
     * @param roomData Metadata about the room.
     * @param currPlayersAmount Current number of players in the room.
     * @param status Current status of the room.
     */
    RoomPreview(const RoomData& roomData, unsigned int currPlayersAmount, RoomStatus status)
        : roomData(roomData), currPlayersAmount(currPlayersAmount), status(status) {
    }

    /**
     * @brief Constructs a RoomPreview by copying from another RoomPreview.
     * @param other The RoomPreview to copy from.
     */
    RoomPreview(const RoomPreview& other)
        : roomData(other.roomData), currPlayersAmount(other.currPlayersAmount), status(other.status) {
    }

    /**
     * @brief Destructor.
     */
    ~RoomPreview() = default;

    /**
     * @brief Checks if the game in this room has started.
     * @return True if the room's status is StartingGame, false otherwise.
     */
    bool gameStarted() const {
        return status == RoomStatus::StartingGame;
    }

    /**
     * @brief Marks the room as closing.
     */
    void close() {
        status = RoomStatus::Closing;
    }

    /**
     * @brief Marks the room as starting a game.
     */
    void startGame() {
        status = RoomStatus::StartingGame;
    }

    /**
     * @brief Marks the room as in-game.
     */
    void enterGame() {
        status = RoomStatus::InGame;
    }

    /**
     * @brief Marks the room as not in a game, unless the room is already closing.
     */
    void closeGame() {
        if (status != RoomStatus::Closing) {
            status = RoomStatus::NotInGame;
        }
    }

    RoomData roomData;
    unsigned int currPlayersAmount;
    RoomStatus status;
};

/**
 * @brief Serializes a RoomPreview to JSON.
 * @param j JSON object to store the serialized data.
 * @param roomPreview The RoomPreview to serialize.
 */
inline void to_json(nlohmann::json& j, const RoomPreview& roomPreview) {
    j = nlohmann::json{
        {"RoomData", roomPreview.roomData},
        {"CurrPlayersAmount", roomPreview.currPlayersAmount},
        {"Status", roomPreview.status},
    };
}
