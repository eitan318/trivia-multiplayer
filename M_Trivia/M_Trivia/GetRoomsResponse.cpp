#include "GetRoomsResponse.hpp"

#include "json.hpp"



GetRoomsResponse::GetRoomsResponse(unsigned int status, const std::vector<RoomPreview>& rooms) : 
	Response(status), rooms(rooms) 
{

}



ResponseCodes GetRoomsResponse::getCode() const
{
	return ResponseCodes::C_GetRoomsResponse; 
}

nlohmann::json GetRoomsResponse::getJson() const {
	nlohmann::json j = Response::getJson();
	j["Rooms"] = rooms; // Uses the to_json for PersonalStatistics
	return j;
}

