#pragma once
#include "RequestInfo.hpp"
#include "RequestResult.hpp"

class IRequestHandler {
public:
	virtual bool isRequestRelevant(const RequestInfo&) = 0;
	virtual	RequestResult handleRequest(const RequestInfo&) = 0;
};
