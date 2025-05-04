#pragma once
#include "json.hpp"
#include "Response.hpp"
#include "JoinRoomResponseErrors.hpp"
#include <memory>

/**
 * @class JoinRoomResponse
 * @brief Represents a response containing Status only and no data
 */
class JoinRoomResponse : public Response {
public:
	JoinRoomResponse(std::shared_ptr <JoinRoomResponseErrors> errors) 
		: Response(std::move(errors)) {
		
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