#pragma once
#include "json.hpp"
#include "Response.hpp"

/**
 * @class LoginResponse
 * @brief Represents a response containing Status only and no data
 */
class ResetPasswordResponse : public Response {
public:
	ResetPasswordResponse(unsigned int status) : Response(status) {

	}
	/**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
	unsigned char getCode() const override { return C_ResetPasswordResponse; }

	/**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
	nlohmann::json getJson() const override {
		return baseJson();
	}
};