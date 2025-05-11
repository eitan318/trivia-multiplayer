#pragma once
#include "json.hpp"

template <typename T>
class JsonRequestPacketDeserializer;


/**
 * @class GetPlayersInRoomRequest
 * @brief Represents a request to get the players in a room.
 */
class GetPlayersInRoomRequest {
    friend class JsonRequestPacketDeserializer<GetPlayersInRoomRequest>;
private:
    unsigned int roomId;
    GetPlayersInRoomRequest(const nlohmann::json& j) :
        roomId(j.at("RoomId")) {

    }

public:


    unsigned int getRoomId() const { return roomId; }

};
