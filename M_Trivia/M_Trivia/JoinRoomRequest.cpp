#include "JoinRoomRequest.hpp"

JoinRoomRequest::JoinRoomRequest(const nlohmann::json &j)
    : roomId(j.at("RoomId")) {}

unsigned int JoinRoomRequest::getRoomId() const { return roomId; }
