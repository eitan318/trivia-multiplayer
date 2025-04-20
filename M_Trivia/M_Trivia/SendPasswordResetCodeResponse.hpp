#pragma once
#include "json.hpp"
#include "Response.hpp"


class SendPasswordResetCodeResponse : public Response{
public:
    unsigned int status;
    unsigned int emailCode;
    std::string username;

    unsigned int getCode() const { return C_SendPasswordResetCodeRequest; }

    nlohmann::json getJson() const {
        return nlohmann::json {
            {"Status", status},
            {"EmailCode", emailCode},
            {"Username", username},
        };
    }
};