#pragma once
#include "Response.hpp"
#include "LoggedUser.hpp"
#include <map>

/**
 * @class GetPlayersInRoomResponse
 * @brief Represents a response containing a list of players in a room.
 */
class GetPlayersInRoomResponse : public  Response<ResponseCodes::C_GetPlayersInRoomResponse> {
private:
    /// A list of player names in the room.
    std::vector<LoggedUser> players;

public:
    GetPlayersInRoomResponse(unsigned int status, const std::vector<LoggedUser>& players) ;

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */

    nlohmann::json getJson() const override;
};
