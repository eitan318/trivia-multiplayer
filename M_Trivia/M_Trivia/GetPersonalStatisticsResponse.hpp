#pragma once 
#include "json.hpp"
#include "PersonalStatistics.hpp"
#include "Response.hpp"

// Forward declaration for to_json
void to_json(nlohmann::json& j, const PersonalStatistics& personalStatistics);

class GetPersonalStatisticsResponse : public Response {
public:
    unsigned int status;
    PersonalStatistics statistics;

    GetPersonalStatisticsResponse(const PersonalStatistics& personalStats) : statistics(personalStats) {

    }

    unsigned int getCode() const override { // Marking as override if Response has a virtual function
        return C_GetPersonalStatsResponse;
    }

    nlohmann::json getJson() const override {
        return nlohmann::json{
            {"Status", status},
            {"Statistics", statistics} // Uses the to_json for PersonalStatistics
        };
    }
};
