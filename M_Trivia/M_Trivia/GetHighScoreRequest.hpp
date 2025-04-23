#pragma once
#include "json.hpp"

/**
 * @class GetHighScoreRequest
 * @brief Represents a request to get the highest scores.
 */
struct GetHighScoreRequest {
	// The amount off highest scored players
	unsigned int topPlayersLimit;

	/**
	 * @brief Deserializes a JSON object into a GetHighScoreRequest  object.
	 *
	 * @param j The JSON object to deserialize.
	 * @param request The GetHighScoreRequest  object to populate.
	 */
	friend void from_json(const nlohmann::json& j, GetHighScoreRequest& request) {
		j.at("TopPlayersLimit").get_to(request.topPlayersLimit);
	}
};