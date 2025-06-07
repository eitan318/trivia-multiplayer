#pragma once
#include "Response.hpp"
#include "JoinRoomResponseErrors.hpp"

/**
 * @class JoinRoomResponse
 * @brief Represents a response containing Status only and no data
 */
class JoinRoomResponse : public Response {
public:
	JoinRoomResponse(JoinRoomResponseErrors* errors);

	/**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
	ResponseCodes getCode() const override ;
};
