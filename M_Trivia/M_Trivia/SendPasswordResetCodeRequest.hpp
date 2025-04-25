#pragma once
#include <string>
#include "json.hpp"

/**
 * @class SendPasswordResetCodeRequest
 * @brief Represents a request to send the password-reset code to an email.
 */
struct SendPasswordResetCodeRequest {
	// Target email
	std::string email;

	/**
  * @brief Deserializes a JSON object into a SendPasswordResetCodeRequest object.
  *
  * @param j The JSON object to deserialize.
  * @param request The SendPasswordResetCodeRequest object to populate.
  */
	friend void from_json(const nlohmann::json& j, SendPasswordResetCodeRequest& request) {
		j.at("Email").get_to(request.email);
	}
};