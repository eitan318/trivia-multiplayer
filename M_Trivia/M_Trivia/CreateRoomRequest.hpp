#pragma once
#include <string>
#include "json.hpp"

struct CreateRoomRequest {
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;


	friend void from_json(const nlohmann::json& j, CreateRoomRequest& request) {
		j.at("AnswerTimeout").get_to(request.answerTimeout);
		j.at("MaxUsers").get_to(request.maxUsers);
		j.at("QuestionCount").get_to(request.questionCount);
		j.at("RoomName").get_to(request.roomName);
	}
};
