#pragma once
#include "json.hpp"

template <typename T> class JsonRequestPacketDeserializer;

/**
 * @class JoinRoomRequest
 * @brief Represents a request to join a room.
 */
class JoinRoomRequest {
  friend class JsonRequestPacketDeserializer<JoinRoomRequest>;

private:
  unsigned int roomId;

public:
  JoinRoomRequest(const nlohmann::json &j);

  unsigned int getRoomId() const;
};
