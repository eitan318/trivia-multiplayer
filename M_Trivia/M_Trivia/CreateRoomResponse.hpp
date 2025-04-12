#pragma once
#include "json.hpp"
#include "Response.hpp"


class CreateRoomResponse : public Response{
public:
	unsigned int status;

    unsigned int getCode() const { return C_CreateRoomResponse; }

    nlohmann::json getJson() const{
        return nlohmann::json {
            {"Status", status}
        };
    }
};