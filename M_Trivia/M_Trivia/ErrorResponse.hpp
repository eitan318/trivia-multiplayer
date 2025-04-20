#pragma once
#include <string>
#include "json.hpp"
#include "Response.hpp"

struct ErrorResponse : public Response{
public:
    unsigned int getCode() const { return C_ErrorResponse; }

	std::string message;


    nlohmann::json getJson() const{
        return nlohmann::json {
            {"Message", message},
        };
    }
};