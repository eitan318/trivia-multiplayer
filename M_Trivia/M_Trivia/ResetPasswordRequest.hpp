#pragma once
#include <string>
#include "json.hpp"

/**
 * @class JoinRoomReques
 * @brief Represents a request to join to reset a user's password.
 */
struct ResetPasswordRequest  {
	// Username who wants to change his password
	std::string username;

	// His new password
	std::string newPassword;

	/**
	  * @brief Deserializes a JSON object into a ResetPasswordRequest object.
	  *
	  * @param j The JSON object to deserialize.
	  * @param request The ResetPasswordRequest object to populate.
	  */
	friend void from_json(const nlohmann::json& j, ResetPasswordRequest& request) {
		j.at("Username").get_to(request.username);
		j.at("NewPassword").get_to(request.newPassword);
	}
};