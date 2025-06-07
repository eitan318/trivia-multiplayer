#pragma once
#include "RoomPreview.hpp"
#include "Response.hpp"
#include <vector>

/**
 * @class GetRoomsResponse
 * @brief class represents a response containing the rooms
 */
class GetRoomsResponse : public Response{
private:
    std::vector<RoomPreview> rooms;
public:
    GetRoomsResponse() = delete;
    GetRoomsResponse(unsigned int status, const std::vector<RoomPreview>& rooms);

    /**
     * @brief Gets the response code for this response.
     * @return The response code as an unsigned integer.
     */
    ResponseCodes getCode() const override ;

    /**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
    nlohmann::json getJson() const override ;
};





