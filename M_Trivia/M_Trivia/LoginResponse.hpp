#pragma once
#include "json.hpp"
#include "Response.hpp"
#include "LoginResponseErrors.hpp"

/**
 * @class LoginResponse
 * @brief Represents a response containing Status only and no data
 */
class LoginResponse : public Response {
public:
	LoginResponse(std::shared_ptr <LoginResponseErrors> errors)
		: Response(std::move(errors)) {
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
		nlohmann::json j = baseJson();
		return j;
	}
};