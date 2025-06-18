#pragma once
#include "json.hpp"
#include <string>
#include "RoomData.hpp"

template <typename T> class JsonRequestPacketDeserializer;

/**
 * @class CreateRoomRequest
 * @brief Represents a request to create a room with specific settings.
 */
class CreateRoomRequest {
  friend class JsonRequestPacketDeserializer<CreateRoomRequest>;

private:
	RoomData m_roomData;

  CreateRoomRequest(const nlohmann::json &j);

public:
	RoomData getRoomData() const;
};
