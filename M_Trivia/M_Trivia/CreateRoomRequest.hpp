#pragma once
#include "json.hpp"
#include <string>

template <typename T> class JsonRequestPacketDeserializer;

/**
 * @class CreateRoomRequest
 * @brief Represents a request to create a room with specific settings.
 */
class CreateRoomRequest {
  friend class JsonRequestPacketDeserializer<CreateRoomRequest>;

private:
  std::string roomName;
  unsigned int maxUsers;
  unsigned int questionCount;
  double answerTimeout;

  CreateRoomRequest(const nlohmann::json &j);

public:
  std::string getRoomName() const;
  unsigned int getMaxUsers() const;
  unsigned int getQuestionCount() const;
  double getAnswerTimeout() const;
};
