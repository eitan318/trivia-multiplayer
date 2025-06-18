#include "CreateRoomResponse.hpp"

#include "json.hpp"

CreateRoomResponse::CreateRoomResponse(std::unique_ptr<CreateRoomResponseErrors> errors, const RoomData& roomData)
    : Response(std::move(errors)), roomData(roomData) {
}


nlohmann::json CreateRoomResponse::getJson() const {
	nlohmann::json j = Response::getJson();
	j["RoomData"] = roomData;
	return j;
}



