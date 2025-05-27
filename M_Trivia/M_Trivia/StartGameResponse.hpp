#pragma once
#include "Response.hpp"

/**
 * @class StartRoomResponse
 * @brief Represents a response containing Status only and no data
 */
class StartGameResponse : public Response {
public:
	StartGameResponse(unsigned int status);

	/**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
	ResponseCodes getCode() const override;


	/**
	 * @brief Deleted default constructor to enforce proper initialization.
	 */
	LeaveRoomResponse() = delete;
};	