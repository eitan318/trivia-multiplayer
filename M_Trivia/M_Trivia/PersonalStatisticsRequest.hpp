#pragma once
#include "json.hpp"

template <typename T>
class JsonRequestPacketDeserializer;


/**
 * @class PersonalStatisticsRequest
 * @brief Represents a request to get the statistics of the player/user.
 */
class PersonalStatisticsRequest {
    friend class JsonRequestPacketDeserializer<PersonalStatisticsRequest>;
private:
    PersonalStatisticsRequest() = default;
public:

};


