#pragma once
#include "json.hpp"
#include "Response.hpp"

/**
 * @class LogoutResponse
 * @brief Represents a response containing Status only and no data
 */
class LogoutResponse : public Response {
public:
	LogoutResponse(unsigned int status) : Response(status) {

	}

	/**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
	ResponseCodes getCode() const override { return ResponseCodes::C_LoginResponse; }

	/**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
	nlohmann::json getJson() const override {
		return baseJson();
	}
};