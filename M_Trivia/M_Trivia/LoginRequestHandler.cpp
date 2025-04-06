#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
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
	switch (requestInfo.code) {
	case C_LoginRequest:
	{
		return login(requestInfo);
	}
	case C_SignupRequest:
	{
		return signup(requestInfo);
	}
	default:
		ErrorResponse errorResponse;
		errorResponse.message = "Invalid msg code.";

		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);
		requestResult.newHandler = new LoginRequestHandler(this->m_handlerFactory);

		return requestResult;
	}
}

RequestResult LoginRequestHandler::login(const RequestInfo& requestInfo)
{
	LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);

	LoginResponse loginResponse;
	loginResponse.status = this->m_handlerFactory.getLoginManager().login(request.username, request.password);

	RequestResult requestResult;
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(loginResponse);
	requestResult.newHandler = new LoginRequestHandler(this->m_handlerFactory);
	return requestResult;
}

RequestResult LoginRequestHandler::signup(const RequestInfo& requestInfo)
{
	SignupRequest request;
	try {
		request = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);
	}
	catch (const std::runtime_error& e) {
		RequestResult res;
		ErrorResponse errResponse;
		errResponse.message = e.what();
		res.response = JsonResponsePacketSerializer::serializeResponse(errResponse);
		res.newHandler = new LoginRequestHandler(this->m_handlerFactory);
		return res;
	}

	
	SignupResponse signupResponse;
	signupResponse.status = this->m_handlerFactory.getLoginManager().signup(request.userRecord);
	RequestResult requestResult;
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(signupResponse);
	requestResult.newHandler = new LoginRequestHandler(this->m_handlerFactory);
	return requestResult;
}
