#pragma once
#include "Response.hpp"
#include "VerifyPasswordResetCodeResponseErrors.hpp"

/**
 * @class LoginResponse
 * @brief Represents a response containing Status only and no data
 */
class VerifyPasswordResetCodeResponse : public Response {
private:
    std::string passwordResetTocken;

public:
    VerifyPasswordResetCodeResponse(VerifyPasswordResetCodeResponseErrors* errors,
        const std::string& passwordResetTocken);

    /**
     * @brief Gets the response code for this response.
     * @return The response code as an unsigned integer.
     */
    ResponseCodes getCode() const override;

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */

    nlohmann::json getJson() const override;
};
