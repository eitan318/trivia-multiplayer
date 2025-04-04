#pragma once
#include "IRequestHandler.h"
#include "Requests.hpp"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

class LoginRequestHandler : public IRequestHandler {
public:
	LoginRequestHandler();
	~LoginRequestHandler();
	bool isRequestRelevant(const RequestInfo&);
	RequestResult handleRequest(const RequestInfo&);
};
