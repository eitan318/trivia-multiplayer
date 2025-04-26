#pragma once
#include "json.hpp"
#include "HighScoreInfo.hpp"
#include "Response.hpp"

/**
 * @class SignupResponse
 * @brief Represents a response containing Status only and no data
 */
class SignupResponse : public Response {
public:
	SignupResponse(unsigned int status) : Response(status) {

	}


	/**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
	unsigned char getCode() const { return C_SignupResponse; }

	/**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
	nlohmann::json getJson() const override {
		return baseJson();
	}
};