#pragma once
#include "json.hpp"
#include "HighScoreInfo.hpp"
#include "Response.hpp"

void to_json(nlohmann::json& j, const HighScoreInfo& highScoreInfo);

/**
 * @class GetHighScoreResponse
 * @brief Represents a response status, statistics
 */
class GetHighScoreResponse : public Response{
public:

    /**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
    unsigned char getCode() const { return C_GetHighScoreResponse; }

	std::vector<HighScoreInfo> statistics;

    /**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
    nlohmann::json getJson() const override {
        nlohmann::json j = baseJson();
        j["Statistics"] = statistics; 
        return j;
    }
};


