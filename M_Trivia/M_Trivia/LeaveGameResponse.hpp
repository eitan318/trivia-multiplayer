#pragma once
#include "Response.hpp"
#include "GeneralResponseErrors.hpp"

/**
 * @class CloseRoomResponse
 * @brief Represents a response containing Status only and no data
 */
class LeaveGameResponse : public Response {
public:
	LeaveGameResponse(GeneralResponseErrors* errors);

	/**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
	ResponseCodes getCode() const override;

	/**
	 * @brief Deleted default constructor to enforce proper initialization.
	 */
	LeaveGameResponse() = delete;
};