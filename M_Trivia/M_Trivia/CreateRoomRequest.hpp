#pragma once
#include <string>
#include "json.hpp"

/**
 * @class CreateRoomRequest
 * @brief Represents a request to create a room with specific settings.
 */
struct CreateRoomRequest {
    /// The name of the room.
    std::string roomName;

    /// The maximum number of users allowed in the room.
    unsigned int maxUsers;

    /// The number of questions in the room's quiz.
    unsigned int questionCount;

    /// The timeout (in seconds) for answering a question.
    unsigned int answerTimeout;

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
