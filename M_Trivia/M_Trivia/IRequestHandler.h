#pragma once
#include "RequestInfo.hpp"

class IRequestHandler {
public:
	bool isRequestRelevant(const RequestInfo&);
	void handleRequest(const RequestInfo&);
};
