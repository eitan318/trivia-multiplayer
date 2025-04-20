#pragma once
#include <string>
#include "json.hpp"

struct LoginRequest {
	std::string username;
	std::string password;


	friend void from_json(const nlohmann::json& j, LoginRequest& request) {
		j.at("Username").get_to(request.username);
		j.at("Password").get_to(request.password);
	}
};
