#pragma once
#include "json.hpp"
#include "Response.hpp"

/**
 * @class LogoutResponse
 * @brief Represents a response containing Status only and no data
 */
class LogoutResponse : public Response {
public:


	/**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
	unsigned char getCode() const { return C_LoginResponse; }

	/**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
	nlohmann::json getJson() const override {
		return baseJson();
	}
};