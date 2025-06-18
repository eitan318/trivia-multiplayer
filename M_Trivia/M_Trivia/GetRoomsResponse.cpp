#include "GetRoomsResponse.hpp"

#include "json.hpp"



GetRoomsResponse::GetRoomsResponse(unsigned int status, const std::vector<RoomPreview>& rooms) : 
	Response(status), rooms(rooms) 
{

}


nlohmann::json GetRoomsResponse::getJson() const {
	nlohmann::json j = Response::getJson();
	j["Rooms"] = rooms; // Uses the to_json for PersonalStatistics
	return j;
}

