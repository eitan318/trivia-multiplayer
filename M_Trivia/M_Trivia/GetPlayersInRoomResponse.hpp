#pragma once
#include "Response.hpp"
#include "LoggedUser.hpp"
#include <map>

/**
 * @class GetPlayersInRoomResponse
 * @brief Represents a response containing a list of players in a room.
 */
class GetPlayersInRoomResponse : public Response {
private:
    /// A list of player names in the room.
    std::map<std::string,LoggedUser> players;

public:
    GetPlayersInRoomResponse() = delete;
    GetPlayersInRoomResponse(unsigned int status, const std::map<std::string,LoggedUser>& players) ;

    /**
     * @brief Gets the response code for this response.
     * @return The response code as an unsigned integer.
     */
    ResponseCodes getCode() const override;

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */

    nlohmann::json getJson() const override;
};
