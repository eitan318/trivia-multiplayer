#pragma once
#include <string>
#include "json.hpp"

struct ResetPasswordRequest  {
	std::string username;
	std::string newPassword;


	friend void from_json(const nlohmann::json& j, ResetPasswordRequest& request) {
		j.at("Username").get_to(request.username);
		j.at("NewPassword").get_to(request.newPassword);
	}
};