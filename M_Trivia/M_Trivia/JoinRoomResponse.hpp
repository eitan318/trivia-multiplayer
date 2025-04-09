#pragma once
#include "json.hpp"
#include "Response.hpp"

class JoinRoomResponse : public Response{
public:
	unsigned int status;

    unsigned int getCode() const { return C_JoinRoomResponse; }

    nlohmann::json getJson() const {
        return nlohmann::json {
            {"status", status}
        };
    }
};
