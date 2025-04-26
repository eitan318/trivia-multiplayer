#pragma once
#include "json.hpp"

/**
 * @class JoinRoomRequest
 * @brief Represents a request to join a room.
 */
class JoinRoomRequest {
    friend void from_json(const nlohmann::json& j, JoinRoomRequest& request);

private:
    unsigned int roomId;

public:
    JoinRoomRequest() = default;

    unsigned int getRoomId() const { return roomId; }

    /**
     * @brief Deserializes a JSON object into a JoinRoomRequest object.
     *
     * @param j The JSON object to deserialize.
     * @param request The JoinRoomRequest object to populate.
     */
    friend void from_json(const nlohmann::json& j, JoinRoomRequest& request) {
        j.at("RoomId").get_to(request.roomId);
    }
};
