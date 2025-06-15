#include "VerifyPasswordResetCodeResponse.hpp"
#include "Response.hpp"
#include "json.hpp"

VerifyPasswordResetCodeResponse::VerifyPasswordResetCodeResponse(
    std::unique_ptr<VerifyPasswordResetCodeResponseErrors> errors,
    const std::string& passwordResetTocken)
    : Response(std::move(errors)), passwordResetTocken(passwordResetTocken) {
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
