#pragma once
#include "json.hpp"
#include "Response.hpp"

class SignupResponse : public Response{
public:
	unsigned int status;

    unsigned int getCode() const { return C_SignupResponse; }

    nlohmann::json getJson() const {
        return nlohmann::json {
            {"Status", status},
        };
    }
};