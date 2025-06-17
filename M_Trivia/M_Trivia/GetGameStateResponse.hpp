#pragma once
#include "Response.hpp"
#include "PlayerResults.hpp"
#include <vector>
#include "GameStatus.hpp"


/**
 * @class GetHighScoreResponse
 * @brief Represents a response status, statistics
 */
class GetGameStateResponse : public Response<ResponseCodes::C_GetGameStateResponse, IResponseErrors> {
private:
    GameStatus m_gameStatus;
public:
    GetGameStateResponse(unsigned int status, const GameStatus gameStatus);


    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const override;
};


