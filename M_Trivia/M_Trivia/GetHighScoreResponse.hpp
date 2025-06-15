#pragma once
#include "HighScoreInfo.hpp"
#include "Response.hpp"
#include <vector>


/**
 * @class GetHighScoreResponse
 * @brief Represents a response status, statistics
 */
class GetHighScoreResponse : public Response{
private:
    std::vector<HighScoreInfo> statistics;

public:
    GetHighScoreResponse(unsigned int status, const std::vector<HighScoreInfo>& statistics);

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


