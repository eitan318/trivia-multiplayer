#pragma once
#include "json.hpp"
#include "Response.hpp"


class LoginResponse : public Response {
public:
	unsigned int status;

    unsigned int getCode() const { return C_LoginResponse; }

    nlohmann::json getJson() const {
         return nlohmann::json {
            {"status", status},
        };
    }
};