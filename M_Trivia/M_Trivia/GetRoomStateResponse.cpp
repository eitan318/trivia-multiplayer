#include "GetRoomStateResponse.hpp"

GetRoomStateResponse::GetRoomStateResponse(unsigned int status,
	RoomState roomState) : Response(status), m_roomState(roomState)
{
}


nlohmann::json GetRoomStateResponse::getJson() const
{
	nlohmann::json j = Response::getJson();
	j["RoomState"] = m_roomState;
	return j;
}



