#pragma once
#include "json.hpp"
#include "Response.hpp"


class SendPasswordResetCodeResponse : public Response{
private:
  unsigned int emailCode;
    std::string username;
public:
    SendPasswordResetCodeResponse() = delete;
    SendPasswordResetCodeResponse(unsigned int status, unsigned int emailCode, const std::string& username)
        : Response(status), emailCode(emailCode), username(username) {

    }

    /**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
    unsigned char getCode() const override { return C_SendPasswordResetCodeResponse; }

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