#pragma once
#include <string>
#include "json.hpp"

struct SendPasswordResetCodeRequest {
	std::string email;

	friend void from_json(const nlohmann::json& j, SendPasswordResetCodeRequest& request) {
		j.at("Email").get_to(request.email);
	}
};