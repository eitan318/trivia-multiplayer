#pragma once
#include <string>
#include "json.hpp"

/**
 * @class CreateRoomRequest
 * @brief Represents a request to create a room with specific settings.
 */
class CreateRoomRequest {
    friend void from_json(const nlohmann::json& j, CreateRoomRequest& request);

private:
    std::string roomName;
    unsigned int maxUsers;
    unsigned int questionCount;
    unsigned int answerTimeout;

public:
    CreateRoomRequest() = default;

    const std::string& getRoomName() const { return roomName; }
    unsigned int getMaxUsers() const { return maxUsers; }
    unsigned int getQuestionCount() const { return questionCount; }
    unsigned int getAnswerTimeout() const { return answerTimeout; }

    /**
     * @brief Deserializes a JSON object into a CreateRoomRequest object.
     *
     * @param j The JSON object to deserialize.
     * @param request The CreateRoomRequest object to populate.
     */
    friend void from_json(const nlohmann::json& j, CreateRoomRequest& request) {
        j.at("AnswerTimeout").get_to(request.answerTimeout);
        j.at("MaxUsers").get_to(request.maxUsers);
        j.at("QuestionCount").get_to(request.questionCount);
        j.at("RoomName").get_to(request.roomName);
    }
};
