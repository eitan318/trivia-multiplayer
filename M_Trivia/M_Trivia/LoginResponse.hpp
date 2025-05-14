#pragma once
#include "Response.hpp"
#include "LoginResponseErrors.hpp"


/**
 * @class LoginResponse
 * @brief Represents a response containing Status only and no data
 */
class LoginResponse : public Response {
public:
	LoginResponse(LoginResponseErrors* errors);

	/**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
	ResponseCodes getCode() const override;
};
