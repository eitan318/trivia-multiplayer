#include "CreateRoomResponse.hpp"

#include "json.hpp"

CreateRoomResponse::CreateRoomResponse(CreateRoomResponseErrors* errors, const RoomData& roomData)
    : Response(errors), roomData(roomData) {
}


ResponseCodes CreateRoomResponse::getCode() const {
    return ResponseCodes::C_CreateRoomResponse; 
}

nlohmann::json CreateRoomResponse::getJson() const {
	nlohmann::json j = Response::getJson();
	j["RoomData"] = roomData;
	return j;
}



