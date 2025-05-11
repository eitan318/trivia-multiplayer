#pragma once
#include "json.hpp"

template <typename T>
class JsonRequestPacketDeserializer;


/**
 * @class GetHighScoreRequest
 * @brief Represents a request to get the highest scores.
 */
class GetHighScoreRequest {
    friend class JsonRequestPacketDeserializer<GetHighScoreRequest>;
private:
    unsigned int topPlayersLimit;

    GetHighScoreRequest(const nlohmann::json& j) :
        topPlayersLimit(j.at("TopPlayersLimit"))
    {
    }
public:
    unsigned int getTopPlayersLimit() const { return topPlayersLimit; }

};
