#include "GetGameResultsResponse.hpp"

GetGameResultsResponse::GetGameResultsResponse(unsigned int status, const std::vector<PlayerResults>& results) :
	Response(status), _results(results)
{
}

nlohmann::json GetGameResultsResponse::getJson() const
{
	nlohmann::json j = Response::getJson();
	j["Results"] = _results;
	return j;
}
