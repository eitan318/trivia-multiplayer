#pragma once
#include <string>
#include "json.hpp"

/**
 * @class JoinRoomReques
 * @brief Represents a request to join to login.
 */
struct LoginRequest {
	// Username that wants to login
	std::string username;
	// His password(will be hash in future)
	std::string password;

	/**
	  * @brief Deserializes a JSON object into a LoginRequest object.
	  *
	  * @param j The JSON object to deserialize.
	  * @param request The LoginRequest object to populate.
	  */
	friend void from_json(const nlohmann::json& j, LoginRequest& request) {
		j.at("Username").get_to(request.username);
		j.at("Password").get_to(request.password);
	}
};
