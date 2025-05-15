#include "GetPlayersInRoomRequest.hpp"

GetPlayersInRoomRequest::GetPlayersInRoomRequest(const nlohmann::json &j)
    : roomId(j.at("RoomId")) {}
unsigned int GetPlayersInRoomRequest::getRoomId() const { return roomId; }
