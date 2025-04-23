#pragma once
#include "json.hpp"
#include "Response.hpp"

/**
 * @class GetPlayersInRoomResponse
 * @brief Represents a response containing a list of players in a room.
 */
class GetPlayersInRoomResponse : public Response {
public:
    /// A list of player names in the room.
    std::vector<std::string> players;

    /**
     * @brief Gets the response code for this response.
     * @return The response code as an unsigned integer.
     */
    unsigned int getCode() const { return C_GetPlayersInRoomResponse; }

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const {
        return nlohmann::json{
            {"Players", players},
        };
    }
};
