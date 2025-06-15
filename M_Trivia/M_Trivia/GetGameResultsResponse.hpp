#pragma once
#include "Response.hpp"
#include "PlayerResults.hpp"
#include <vector>


/**
 * @class GetHighScoreResponse
 * @brief Represents a response status, statistics
 */
class GetGameResultsResponse : public Response<ResponseCodes::C_GetGameResultsResponse, IResponseErrors> {
private:
    std::vector<PlayerResults> _results;

public:
    GetGameResultsResponse(unsigned int status, const std::vector<PlayerResults>& results);


    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const override;
};


