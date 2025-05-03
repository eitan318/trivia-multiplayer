#pragma once
#include "json.hpp"

/**
 * @class PersonalStatisticsRequest
 * @brief Represents a request to get the statistics of the player/user.
 */
class PersonalStatisticsRequest {
    friend void from_json(const nlohmann::json& j, PersonalStatisticsRequest& request);

private:

public:
    PersonalStatisticsRequest() = default;


    /**
     * @brief Deserializes a JSON object into a PersonalStatisticsRequest object.
     *
     * @param j The JSON object to deserialize.
     * @param request The PersonalStatisticsRequest object to populate.
     */
    friend void from_json(const nlohmann::json& j, PersonalStatisticsRequest& request) {
    }
};
