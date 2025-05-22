#pragma once
#include <vector>
#include <ctime>
/**
 * @struct RequestInfo
 * @brief Represents a request's information.
 */
class RequestInfo {
public:
    /**
     * @brief Constructor for creating a RequestInfo object.
     * @param code Request code identifying the type of request.
     * @param receivalTime The time the request was received.
     * @param buffer The data buffer associated with the request.
     */
    RequestInfo(unsigned char code, const time_t& receivalTime,
        const std::vector<char>& buffer);

    unsigned char code;           ///< Request code identifying the type of request.
    time_t receivalTime;          ///< The time the request was received.
    std::vector<char> buffer;     ///< The data buffer associated with the request.

private:
    RequestInfo(); ///< Private default constructor to prevent uninitialized objects.
};

