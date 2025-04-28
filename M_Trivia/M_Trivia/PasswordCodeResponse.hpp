#pragma once
#include "json.hpp"
#include "Response.hpp"
#include "PasswordCodeResponseErrors.hpp"


class PasswordCodeResponse : public Response{
private:
    unsigned int emailCode;
    std::string username;
public:
    PasswordCodeResponse() = delete;
    PasswordCodeResponse(
        std::shared_ptr<PasswordCodeResponseErrors> errors,
        unsigned int randomCode,
        const std::string& username
    )
        : Response(std::move(errors)), emailCode(randomCode), username(username) {
    }


    /**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
    ResponseCodes getCode() const override { return ResponseCodes::C_SendPasswordResetCodeResponse; }

    /**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
    nlohmann::json getJson() const override {
        nlohmann::json j = baseJson();
        j["EmailCode"] = emailCode;
        j["Username"] = username;
        return j;
    }
};