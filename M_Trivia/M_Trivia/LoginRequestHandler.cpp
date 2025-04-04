#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler()
{
}

LoginRequestHandler::~LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return requestInfo.code == C_LoginRequest || 
		requestInfo.code == C_SignupRequest;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	RequestResult requestResult;
	switch (requestInfo.code) {
	case C_LoginRequest:
	{
		LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
		
		LoginResponse loginResponse;
		loginResponse.status = 1;

		requestResult.response = JsonResponsePacketSerializer::serializeResponse(loginResponse);
		requestResult.newHandler = new LoginRequestHandler();
		return requestResult;
	}
	case C_SignupRequest:
	{
		SignupRequest request = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);

		SignupResponse signupResponse;
		signupResponse.status = 1;

		requestResult.response = JsonResponsePacketSerializer::serializeResponse(signupResponse);
		requestResult.newHandler = new LoginRequestHandler();
		return requestResult;
	}
	default:
		return requestResult;
	}
}
