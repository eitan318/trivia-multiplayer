#pragma once
#include "json.hpp"
#include "Response.hpp"

class NoDataResponse : public Response {
public:
    unsigned int status;

    unsigned int getCode() const { return C_NoDataResponse; }

    nlohmann::json getJson() const {
        return nlohmann::json{
            {"Status", status},
        };
    }
};