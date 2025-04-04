#include <vector>
#include <string>
#include "IRequestHandler.h"
struct RequestResult {
	std::vector<char> response;
	IRequestHandler* newHandler;
};