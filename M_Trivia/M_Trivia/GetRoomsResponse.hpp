#pragma once
#include "json.hpp"
#include "RoomData.h"
#include "Response.hpp"

void to_json(nlohmann::json& j, const RoomData& roomData);



class GetRoomsResponse : public Response{
public:
	unsigned int status;
	std::vector<RoomData> rooms;

    unsigned int getCode() const { return C_GetRoomsResponse; }

    nlohmann::json getJson() const {
        return nlohmann::json {
            {"Status", status},
            {"Rooms", rooms}
        };
    }
};





