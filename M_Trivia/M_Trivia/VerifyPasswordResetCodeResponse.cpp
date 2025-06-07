#include "VerifyPasswordResetCodeResponse.hpp"
#include "Response.hpp"
#include "json.hpp"

VerifyPasswordResetCodeResponse::VerifyPasswordResetCodeResponse(
    VerifyPasswordResetCodeResponseErrors* errors,
    const std::string& passwordResetTocken)
    : Response(errors), passwordResetTocken(passwordResetTocken) {
}

/**
 * @brief Gets the response code for this response.
 * @return The response code as an unsigned integer.
 */
ResponseCodes VerifyPasswordResetCodeResponse::getCode() const {
    return ResponseCodes::C_VerifyPasswordResetCodeResponse;
}

/**
 * @brief Converts the response to a JSON object.
 * @return A JSON representation of the response.
 */

nlohmann::json VerifyPasswordResetCodeResponse::getJson() const {
    nlohmann::json j = Response::getJson();
    j["PasswordResetTocken"] = passwordResetTocken;
    return j;
}
