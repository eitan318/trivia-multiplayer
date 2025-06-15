#pragma once
#include "Response.hpp"

/**
 * @class LeaveRoomResponse
 * @brief Represents a response containing Status only and no data
 */
class LeaveRoomResponse : public Response {
public:
	LeaveRoomResponse(unsigned int status);

	/**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
	ResponseCodes getCode() const override;
};