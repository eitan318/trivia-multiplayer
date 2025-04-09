#pragma once
#include "json.hpp"
#include "Response.hpp"

class LogoutResponse : public Response{
public:
	unsigned int status;

    unsigned int getCode() const { return C_LogoutResponse; }

    nlohmann::json getJson() const {
        return nlohmann::json {
            {"status", status},
        };
    }
};