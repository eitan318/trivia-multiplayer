#pragma once
#include "json.hpp"
#include "HighScoreInfo.hpp"
#include "Response.hpp"

void to_json(nlohmann::json& j, const HighScoreInfo& highScoreInfo);

class GetHighScoreResponse : public Response{
public:
    unsigned int getCode() const { return C_GetHighScoreResponse; }

	unsigned int status;
	std::vector<HighScoreInfo> statistics;

    nlohmann::json getJson() const {
        return nlohmann::json {
            {"Status", status},
            {"Statistics", statistics},
        };
    }
};


