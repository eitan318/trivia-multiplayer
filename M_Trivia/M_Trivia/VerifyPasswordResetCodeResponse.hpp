#pragma once
#include "Response.hpp"
#include "VerifyPasswordResetCodeResponseErrors.hpp"

/**
 * @class LoginResponse
 * @brief Represents a response containing Status only and no data
 */
class VerifyPasswordResetCodeResponse : public Response<ResponseCodes::C_VerifyPasswordResetCodeResponse, VerifyPasswordResetCodeResponseErrors> {
private:
    std::string passwordResetTocken;

public:
    VerifyPasswordResetCodeResponse(std::unique_ptr<VerifyPasswordResetCodeResponseErrors> errors,
        const std::string& passwordResetTocken);

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */

    nlohmann::json getJson() const override;
};
