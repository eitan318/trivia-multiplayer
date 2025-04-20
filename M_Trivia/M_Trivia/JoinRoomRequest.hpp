#pragma once
#include "json.hpp"

struct JoinRoomRequest {
	unsigned int roomId;

	friend void from_json(const nlohmann::json& j, JoinRoomRequest& request) {
		j.at("RoomId").get_to(request.roomId);
	}
};
