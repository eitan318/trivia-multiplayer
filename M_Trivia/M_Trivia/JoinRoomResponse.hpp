#pragma once
#include "json.hpp"
#include "Response.hpp"

/**
 * @class JoinRoomResponse
 * @brief Represents a response containing Status only and no data
 */
class JoinRoomResponse : public Response {
public:
	JoinRoomResponse(unsigned int status) : Response(status) {
		
	}

	/**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
	ResponseCodes getCode() const override { return ResponseCodes::C_JoinRoomResponse; }

	/**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
	nlohmann::json getJson() const override {
		return baseJson();
	}
};