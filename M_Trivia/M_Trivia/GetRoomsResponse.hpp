#pragma once
#include "RoomPreview.hpp"
#include "Response.hpp"
#include <vector>

/**
 * @class GetRoomsResponse
 * @brief class represents a response containing the rooms
 */
class GetRoomsResponse : public  Response<ResponseCodes::C_GetRoomsResponse> {
private:
    std::vector<RoomPreview> rooms;
public:
    GetRoomsResponse(unsigned int status, const std::vector<RoomPreview>& rooms);

    /**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
    nlohmann::json getJson() const override ;
};





