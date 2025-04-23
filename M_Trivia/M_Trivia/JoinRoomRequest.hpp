#pragma once
#include "json.hpp"

/**
 * @class JoinRoomReques
 * @brief Represents a request to join to a room.
 */
struct JoinRoomRequest { 
	// The id of room to join to
	unsigned int roomId;

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
