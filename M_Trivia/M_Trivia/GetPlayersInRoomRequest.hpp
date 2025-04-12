#pragma once
#include "json.hpp"


struct GetPlayersInRoomRequest {
	unsigned int roomId;

	friend void from_json(const nlohmann::json& j, GetPlayersInRoomRequest& request) {
		j.at("RoomId").get_to(request.roomId);
	}
};