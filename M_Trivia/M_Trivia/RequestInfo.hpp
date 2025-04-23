#pragma once
#include <string>
#include <ctime>
#include <vector>

/**
 * @struct RequestInfo
 * @brief Represents a requests info
 */
struct RequestInfo {
	unsigned char code;
	time_t receivalTime;
	std::vector<char> buffer;
};