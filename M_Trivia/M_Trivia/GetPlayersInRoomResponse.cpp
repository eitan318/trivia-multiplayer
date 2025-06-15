#include "GetPlayersInRoomResponse.hpp"
#include "json.hpp"


GetPlayersInRoomResponse::GetPlayersInRoomResponse(unsigned int status, const std::vector<LoggedUser>& players) : Response(status), players(players) {

}


nlohmann::json GetPlayersInRoomResponse::getJson() const {
        nlohmann::json j = Response::getJson();
        j["Players"] = players; 
        return j;
    }


