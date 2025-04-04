#pragma once
#include <string>
#include <ctime>
#include <vector>

struct RequestInfo {
	unsigned int code;
	time_t receivalTime;
	std::vector<char> buffer;
};