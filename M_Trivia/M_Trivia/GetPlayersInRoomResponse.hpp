#pragma once
#include "json.hpp"
#include "Response.hpp"


class GetPlayersInRoomResponse : public Response{
public:
	std::vector<std::string> players;

    unsigned int getCode() const { return C_GetPlayersInRoomResponse; }

    nlohmann::json getJson() const {
        return nlohmann::json  {
            {"Players", players},
        };
    }
};