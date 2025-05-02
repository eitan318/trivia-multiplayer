#pragma once
#include "json.hpp"
#include "PersonalStatistics.hpp"
#include "Response.hpp"

/**
 * @class GetPersonalStatisticsResponse
 * @brief Represents a response containing personal statistics.
 */
class GetPersonalStatisticsResponse : public Response {
private:
    PersonalStatistics statistics;

public:

    GetPersonalStatisticsResponse() = delete;
    /**
     * @brief Constructor for GetPersonalStatisticsResponse.
     * @param personalStats The personal statistics data.
     */
    GetPersonalStatisticsResponse(const PersonalStatistics& personalStats, unsigned int status)
        : Response(status), statistics(personalStats) {
    }

    /**
     * @brief Gets the response code for this response.
     * @return The response code as an unsigned integer.
     */
    ResponseCodes getCode() const override {
        return ResponseCodes::C_GetPersonalStatsResponse;
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
