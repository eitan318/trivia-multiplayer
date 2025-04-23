#pragma once
#include "json.hpp"

/**
 * @class GetPlayersInRoomRequest
 * @brief Represents a request to get the players in a room.
 */
struct GetPlayersInRoomRequest {
	// The id of the room containing the players
	unsigned int roomId;

	/**
	 * @brief Deserializes a JSON object into a GetPlayersInRoomRequest object.
	 *
	 * @param j The JSON object to deserialize.
	 * @param request The GetPlayersInRoomRequest object to populate.
	 */
	friend void from_json(const nlohmann::json& j, GetPlayersInRoomRequest& request) {
		j.at("RoomId").get_to(request.roomId);
	}
};