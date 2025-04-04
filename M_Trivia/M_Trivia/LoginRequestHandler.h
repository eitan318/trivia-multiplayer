#pragma once
#include "IRequestHandler.h"
#include "Requests.hpp"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "Responses.hpp";

class LoginRequestHandler : public IRequestHandler {
public:
	LoginRequestHandler();
	~LoginRequestHandler();
	bool isRequestRelevant(const RequestInfo&);
	RequestResult handleRequest(const RequestInfo&);
};
