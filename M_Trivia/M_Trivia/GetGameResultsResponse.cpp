#include "GetGameResultsResponse.hpp"

GetGameResultsResponse::GetGameResultsResponse(unsigned int status, const std::vector<PlayerResults>& results) :
	Response(status), _results(results)
{
}

ResponseCodes GetGameResultsResponse::getCode() const
{
	return ResponseCodes::C_GetGameResultsResponse;
}

nlohmann::json GetGameResultsResponse::getJson() const
{
	return nlohmann::json();
}
