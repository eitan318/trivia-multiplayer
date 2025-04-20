#pragma once
#include "json.hpp"


struct GetHighScoreRequest {
	unsigned int topPlayersLimit;
	unsigned int status;

	friend void from_json(const nlohmann::json& j, GetHighScoreRequest& request) {
		j.at("Status").get_to(request.status);
		j.at("TopPlayersLimit").get_to(request.topPlayersLimit);
	}
};