#pragma once
#include "json.hpp"
#include "Response.hpp"
#include "LoggedUser.h"

/**
 * @class GetPlayersInRoomResponse
 * @brief Represents a response containing a list of players in a room.
 */
class GetPlayersInRoomResponse : public Response {
private:
    /// A list of player names in the room.
    std::vector<LoggedUser> players;

public:
    GetPlayersInRoomResponse() = delete;
    GetPlayersInRoomResponse(unsigned int status, const std::vector<LoggedUser>& players) : Response(status), players(players) {

    }

    /**
     * @brief Gets the response code for this response.
     * @return The response code as an unsigned integer.
     */
    ResponseCodes getCode() const override { return ResponseCodes::C_GetPlayersInRoomResponse; }

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const override {
        nlohmann::json j = baseJson();
        j["Players"] = players; 
        return j;
    }
};
