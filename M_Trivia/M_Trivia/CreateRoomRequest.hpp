#pragma once
#include <string>

template <typename T>
class JsonRequestPacketDeserializer;

/**
 * @class CreateRoomRequest
 * @brief Represents a request to create a room with specific settings.
 */
class CreateRoomRequest {
    friend class JsonRequestPacketDeserializer<CreateRoomRequest>;
private:
    const std::string& roomName;
    unsigned int maxUsers;
    unsigned int questionCount;
    double answerTimeout;


    CreateRoomRequest(const nlohmann::json& j)
        : roomName(j.at("RoomName")),
        maxUsers(j.at("MaxUsers")),
        questionCount(j.at("QuestionCount")),
        answerTimeout(j.at("AnswerTimeout")) {
    }


public:
    const std::string& getRoomName() const { return roomName; }
    unsigned int getMaxUsers() const { return maxUsers; }
    unsigned int getQuestionCount() const { return questionCount; }
    double getAnswerTimeout() const { return answerTimeout; }
};
