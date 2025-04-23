#pragma once 
#include "json.hpp"
#include "PersonalStatistics.hpp"
#include "Response.hpp"

// Forward declaration for to_json
void to_json(nlohmann::json& j, const PersonalStatistics& personalStatistics);

/**
 * @class GetPersonalStatisticsResponse
 * @brief Represents a response containing personal statistics
 */
class GetPersonalStatisticsResponse : public Response {
public:
    unsigned int status;
    PersonalStatistics statistics;

    GetPersonalStatisticsResponse(const PersonalStatistics& personalStats) : statistics(personalStats) { }

    /**
     * @brief Gets the response code for this response.
     * @return The response code as an unsigned integer.
     */
    unsigned int getCode() const override { // Marking as override if Response has a virtual function
        return C_GetPersonalStatsResponse;
    }

    /**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
    nlohmann::json getJson() const override {
        return nlohmann::json{
            {"Status", status},
            {"Statistics", statistics} // Uses the to_json for PersonalStatistics
        };
    }
};
