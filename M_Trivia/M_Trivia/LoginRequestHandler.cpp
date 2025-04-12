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
	LoginRequest request = JsonRequestPacketDeserializer<LoginRequest>::deserializeRequest(requestInfo.buffer);
	try {
		LoginResponse loginResponse;
		loginResponse.status = static_cast<int>(this->m_handlerFactory.getLoginManager().login(request.username, request.password));

		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(loginResponse);
		requestResult.newHandler = new LoginRequestHandler(this->m_handlerFactory);
		return requestResult;
	}
	catch (std::exception e) {
		ErrorResponse errorResponse;
		errorResponse.message = e.what();

		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);
		requestResult.newHandler = new LoginRequestHandler(this->m_handlerFactory);
		return requestResult;
	}


}

RequestResult LoginRequestHandler::signup(const RequestInfo& requestInfo)
{
	try {

		SignupRequest request;
		request = JsonRequestPacketDeserializer<SignupRequest>::deserializeRequest(requestInfo.buffer);
		SignupResponse signupResponse;
		signupResponse.status = static_cast<int>(this->m_handlerFactory.getLoginManager().signup(request.userRecord));
		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(signupResponse);
		requestResult.newHandler = new LoginRequestHandler(this->m_handlerFactory);
		return requestResult;
	}
	catch (const std::runtime_error& e) {
		RequestResult res;
		ErrorResponse errResponse;
		errResponse.message = e.what();
		res.response = JsonResponsePacketSerializer::serializeResponse(errResponse);
		res.newHandler = new LoginRequestHandler(this->m_handlerFactory);
		return res;
	}

	

}
