#include "CreateRoomRequest.hpp"

CreateRoomRequest::CreateRoomRequest(const nlohmann::json &j)
    : m_roomData(j.at("RoomData"))
{ }

RoomData CreateRoomRequest::getRoomData() const 
{ 
    return m_roomData;
}
