#pragma once
#include <string>
#include "json.hpp"

struct CreateRoomRequest {
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;


	friend void from_json(const nlohmann::json& j, CreateRoomRequest& request) {
		j.at("answer_timeout").get_to(request.answerTimeout);
		j.at("max_users").get_to(request.maxUsers);
		j.at("question_count").get_to(request.questionCount);
		j.at("room_name").get_to(request.roomName);
	}
};
