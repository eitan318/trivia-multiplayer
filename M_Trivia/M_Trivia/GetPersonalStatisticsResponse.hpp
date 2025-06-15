#pragma once
#include "PersonalStatistics.hpp"
#include "Response.hpp"

/**
 * @class GetPersonalStatisticsResponse
 * @brief Represents a response containing personal statistics.
 */
class GetPersonalStatisticsResponse : public  Response<ResponseCodes::C_GetPersonalStatsResponse> {
private:
    PersonalStatistics statistics;

public:

    /**
     * @brief Constructor for GetPersonalStatisticsResponse.
     * @param personalStats The personal statistics data.
     */
    GetPersonalStatisticsResponse(const PersonalStatistics& personalStats, unsigned int status);

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const override ;
};
