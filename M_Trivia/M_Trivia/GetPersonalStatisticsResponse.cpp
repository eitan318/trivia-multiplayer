#include "GetPersonalStatisticsResponse.hpp"
#include "json.hpp"

GetPersonalStatisticsResponse::GetPersonalStatisticsResponse(const PersonalStatistics& personalStats, unsigned int status)
	: Response(status), statistics(personalStats) {

}



ResponseCodes GetPersonalStatisticsResponse::getCode() const {
	return ResponseCodes::C_GetPersonalStatsResponse;
}


nlohmann::json GetPersonalStatisticsResponse::getJson() const {
	nlohmann::json j = Response::getJson();
	j["Statistics"] = statistics; // Uses the to_json for PersonalStatistics
	return j;
}


