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
	std::vector<RoomData> rooms;

    /**
     * @brief Gets the response code for this response.
     * @return The response code as an unsigned integer.
     */
    unsigned char getCode() const { return C_GetRoomsResponse; }

    /**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
    nlohmann::json getJson() const override {
        nlohmann::json j = baseJson();
        j["Rooms"] = rooms; // Uses the to_json for PersonalStatistics
        return j;
    }
};





