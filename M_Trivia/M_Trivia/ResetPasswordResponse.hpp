#pragma once
#include "Response.hpp"
#include "ResetPasswordResponseErrors.hpp"

/**
 * @class LoginResponse
 * @brief Represents a response containing Status only and no data
 */
class ResetPasswordResponse : public Response {
public:
	ResetPasswordResponse(ResetPasswordResponseErrors* resetPasswordResponseErrors);
	/**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
	ResponseCodes getCode() const override;
};
