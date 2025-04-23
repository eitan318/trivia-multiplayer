#pragma once
#include "json.hpp"
#include "Response.hpp"


class SendPasswordResetCodeResponse : public Response{
public:
    unsigned int emailCode;
    std::string username;



    /**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
    unsigned char getCode() const { return C_SendPasswordResetCodeResponse; }

    /**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
    nlohmann::json getJson() const {
        return nlohmann::json {
            {"Status", status},
            {"EmailCode", emailCode},
            {"Username", username},
        };
    }
};