#include "CreateRoomRequest.hpp"

CreateRoomRequest::CreateRoomRequest(const nlohmann::json &j)
    : roomName(j.at("RoomName")), maxUsers(j.at("MaxUsers")),
      questionCount(j.at("QuestionCount")),
      answerTimeout(j.at("AnswerTimeout")) {}

std::string CreateRoomRequest::getRoomName() const 
{ 
    return roomName;
}

unsigned int CreateRoomRequest::getMaxUsers() const { return maxUsers; }

unsigned int CreateRoomRequest::getQuestionCount() const {
  return questionCount;
}
double CreateRoomRequest::getAnswerTimeout() const { return answerTimeout; }
