#include <string>
#include <ctime>
#include <vector>

struct Requestinfo {
	unsigned int id;
	time_t receivalTime;
	std::vector<char> buffer;
};