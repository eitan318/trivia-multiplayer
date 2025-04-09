#pragma once
#include "json.hpp"


struct GetPlayersInRoomRequest {
	unsigned int roomId;

	friend void from_json(const nlohmann::json& j, GetPlayersInRoomRequest& request) {
		j.at("room_id").get_to(request.roomId);
	}
};