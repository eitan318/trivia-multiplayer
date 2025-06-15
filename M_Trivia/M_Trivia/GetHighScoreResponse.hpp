#pragma once
#include "HighScoreInfo.hpp"
#include "Response.hpp"
#include <vector>


/**
 * @class GetHighScoreResponse
 * @brief Represents a response status, statistics
 */
class GetHighScoreResponse : public Response<ResponseCodes::C_GetHighScoreResponse>{
private:
    std::vector<HighScoreInfo> statistics;

public:
    GetHighScoreResponse(unsigned int status, const std::vector<HighScoreInfo>& statistics);


    /**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
    nlohmann::json getJson() const override;
};


