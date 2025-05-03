#pragma once
#include "json.hpp"
#include "Response.hpp"
#include "ResetPasswordResponseErrors.hpp"

/**
 * @class LoginResponse
 * @brief Represents a response containing Status only and no data
 */
class ResetPasswordResponse : public Response {
public:
	ResetPasswordResponse(std::shared_ptr<ResetPasswordResponseErrors> resetPasswordResponseErrors)
		: Response(std::move(resetPasswordResponseErrors)) {
	}
	/**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
	ResponseCodes getCode() const override { return ResponseCodes::C_ResetPasswordResponse; }

	/**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
	nlohmann::json getJson() const override {
		nlohmann::json j = baseJson();
		return j;
	}
};