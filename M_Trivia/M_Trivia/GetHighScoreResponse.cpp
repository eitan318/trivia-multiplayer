#include "GetHighScoreResponse.hpp"
#include "json.hpp"


GetHighScoreResponse::GetHighScoreResponse(unsigned int status, const std::vector<HighScoreInfo>& statistics) 
	: Response(status), statistics(statistics) 
{
}


nlohmann::json GetHighScoreResponse::getJson() const {
	nlohmann::json j = Response::getJson();
	j["Statistics"] = statistics; 
	return j;
}


