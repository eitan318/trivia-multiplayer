#pragma once
#include "json.hpp"
#include "PersonalStatistics.hpp"
#include "Response.hpp"

/**
 * @class GetPersonalStatisticsResponse
 * @brief Represents a response containing personal statistics.
 */
class GetPersonalStatisticsResponse : public Response {
public:
    PersonalStatistics statistics;

    /**
     * @brief Constructor for GetPersonalStatisticsResponse.
     * @param personalStats The personal statistics data.
     */
    GetPersonalStatisticsResponse(const PersonalStatistics& personalStats, unsigned int status = C_GetPersonalStatsResponse)
        : Response(status), statistics(personalStats) {
    }

    /**
     * @brief Gets the response code for this response.
     * @return The response code as an unsigned integer.
     */
    unsigned char getCode() const override {
        return C_GetPersonalStatsResponse;
    }

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const override {
        nlohmann::json j = baseJson();
        j["Statistics"] = statistics; // Uses the to_json for PersonalStatistics
        return j;
    }
};
