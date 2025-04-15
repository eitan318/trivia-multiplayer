#pragma once
#include "IRequestHandler.h"
#include "Requests.hpp"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "Responses.hpp"
#include "RequestHandlerFactory.h"
#include <random>
#include <cmath>

#define CODE_DIGITS 6


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
	RequestResult sendPasswordResetEmail(const RequestInfo& requestInfo);
	RequestResult resetPassword(const RequestInfo& requestInfo);
	unsigned int generateRandomCode(unsigned int digsOfCode);

};
