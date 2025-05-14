#pragma once
#include "Response.hpp"
#include "PasswordCodeResponseErrors.hpp"
#include <string>


class PasswordCodeResponse : public Response{
private:
    unsigned int emailCode;
    std::string username;
public:
    PasswordCodeResponse() = delete;
    PasswordCodeResponse(
        PasswordCodeResponseErrors* errors,
        unsigned int randomCode,
        const std::string& username
    );


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
