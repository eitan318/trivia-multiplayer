#pragma once
#include "json.hpp"
#include "RoomData.h"
#include "Response.hpp"

void to_json(nlohmann::json& j, const RoomData& roomData);


/**
 * @class GetRoomsResponse
 * @brief class represents a response containing the rooms
 */
class GetRoomsResponse : public Response{
public:
	unsigned int status;
	std::vector<RoomData> rooms;

    /**
     * @brief Gets the response code for this response.
     * @return The response code as an unsigned integer.
     */
    unsigned int getCode() const { return C_GetRoomsResponse; }

    /**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
    nlohmann::json getJson() const {
        return nlohmann::json {
            {"Status", status},
            {"Rooms", rooms}
        };
    }
};





