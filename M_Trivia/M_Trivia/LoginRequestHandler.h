#pragma once
#include "IRequestHandler.h"
#include "Requests.hpp"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "Responses.hpp"
#include "RequestHandlerFactory.h"


class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler {
public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactory);
	~LoginRequestHandler();
	bool isRequestRelevant(const RequestInfo&);
	RequestResult handleRequest(const RequestInfo&);
private:
	RequestHandlerFactory& m_handlerFactory;
	RequestResult login(const RequestInfo&);
	RequestResult signup(const RequestInfo&);

};
