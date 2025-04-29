#pragma once
#include "json.hpp"

/**
 * @class GetPlayersInRoomRequest
 * @brief Represents a request to get the players in a room.
 */
class GetPlayersInRoomRequest {
    friend void from_json(const nlohmann::json& j, GetPlayersInRoomRequest& request);

private:
    unsigned int roomId;

public:
    GetPlayersInRoomRequest() = default;

    unsigned int getRoomId() const { return roomId; }

    /**
     * @brief Deserializes a JSON object into a GetPlayersInRoomRequest object.
     *
     * @param j The JSON object to deserialize.
     * @param request The GetPlayersInRoomRequest object to populate.
     */
    friend void from_json(const nlohmann::json& j, GetPlayersInRoomRequest& request) {
        j.at("RoomId").get_to(request.roomId);
    }
};
