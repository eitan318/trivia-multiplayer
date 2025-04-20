#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
{
}

LoginRequestHandler::~LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	return requestInfo.code == C_LoginRequest || requestInfo.code == C_ResetPasswordRequest
		|| requestInfo.code == C_SignupRequest || requestInfo.code == C_SendPasswordResetCodeRequest;
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
	case C_SendPasswordResetCodeRequest:
	{
		return sendPasswordResetEmail(requestInfo);
	}
	case C_ResetPasswordRequest:
	{
		return resetPassword(requestInfo);
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
		NoDataResponse loginResponse;
		LoginResponseStatus status = (this->m_handlerFactory.getLoginManager().login(request.username, request.password));
		loginResponse.status = static_cast<int>(status);
		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(loginResponse);
		LoggedUser user;
		user.m_username = request.username;
		if (status != LoginResponseStatus::Success) {
			requestResult.newHandler = new LoginRequestHandler(this->m_handlerFactory);
		}
		else {
			requestResult.newHandler = new MenuRequestHandler(user,this->m_handlerFactory);
		}
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
		NoDataResponse signupResponse;
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


unsigned int  LoginRequestHandler::generateRandomCode(unsigned int digsOfCode) {
	if (digsOfCode == 0) {
		throw std::invalid_argument("Number of digits must be greater than 0");
	}

	unsigned int lowerBound = static_cast<unsigned int>(std::pow(10, digsOfCode - 1));
	unsigned int upperBound = static_cast<unsigned int>(std::pow(10, digsOfCode)) - 1;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(lowerBound, upperBound);

	return dist(gen);
}


RequestResult LoginRequestHandler::sendPasswordResetEmail(const RequestInfo& requestInfo)
{
	try {
		SendPasswordResetCodeRequest request;
		request = JsonRequestPacketDeserializer<SendPasswordResetCodeRequest>::deserializeRequest(requestInfo.buffer);
		unsigned int randomCode = generateRandomCode(CODE_DIGITS);
		SendPasswordResetCodeResponse response;
		response.status = static_cast<int>(this->m_handlerFactory.getLoginManager().sendEmailCode(request.email, randomCode));
		response.emailCode = randomCode;
		response.username = this->m_handlerFactory.getLoginManager().getUsername(request.email);
		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
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



RequestResult LoginRequestHandler::resetPassword(const RequestInfo& requestInfo)
{
	try {
		ResetPasswordRequest request;
		request = JsonRequestPacketDeserializer<ResetPasswordRequest>::deserializeRequest(requestInfo.buffer);
		NoDataResponse response;
		response.status = static_cast<int>(this->m_handlerFactory.getLoginManager().resetPassword(request.username, request.newPassword));
		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
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
