#pragma once
#include "json.hpp"

struct JoinRoomRequest {
	unsigned int roomId;

	friend void from_json(const nlohmann::json& j, JoinRoomRequest& request) {
		j.at("room_id").get_to(request.roomId);
	}
};
