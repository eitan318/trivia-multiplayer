#pragma once
#include "Response.hpp"
#include "RoomState.hpp"

/**
 * @class GetRoomStateResponse
 * @brief Represents a response for geting a room's state.
 */
class GetRoomStateResponse : public Response {
private:
    RoomState m_roomState;

public:
    /**
	* @brief Constructor for GetRoomStateResponse.
	* @param status The status for the response.
	*/
    GetRoomStateResponse(unsigned int status,
        RoomState roomState);


    /**
     * @brief Gets the response code for this response.
     * @return The response code as an unsigned integer.
     */
    ResponseCodes getCode() const override;

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const override;
};
