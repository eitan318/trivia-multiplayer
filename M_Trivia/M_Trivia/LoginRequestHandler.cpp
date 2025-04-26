#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
{
}

LoginRequestHandler::~LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	switch (static_cast<RequestsCodes>(requestInfo.code)) {
	case RequestsCodes::LoginRequest:
	case RequestsCodes::SignupRequest:
	case RequestsCodes::SendPasswordResetCodeRequest:
	case RequestsCodes::ResetPasswordRequest:
		return true;
	default:
		return false;
	}
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	switch (static_cast<RequestsCodes>(requestInfo.code)) {
	case RequestsCodes::LoginRequest:
		return login(requestInfo);
	case RequestsCodes::SignupRequest:
		return signup(requestInfo);
	case RequestsCodes::SendPasswordResetCodeRequest:
		return sendPasswordResetEmail(requestInfo);
	case RequestsCodes::ResetPasswordRequest:
		return resetPassword(requestInfo);
	}
	return {};
}

RequestResult LoginRequestHandler::login(const RequestInfo& requestInfo) const
{
	LoginRequest request = JsonRequestPacketDeserializer<LoginRequest>::deserializeRequest(requestInfo.buffer);
	try {

		LoginResponseStatus status = (this->m_handlerFactory.getLoginManager().login(request.getUsername(), request.getPassword()));
		LoginResponse loginResponse(static_cast<int>(status));
		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(loginResponse);
		LoggedUser user;
		user.m_username = request.getUsername();
		if (status != LoginResponseStatus::Success) {
			requestResult.newHandler = new LoginRequestHandler(this->m_handlerFactory);
		}
		else {
			requestResult.newHandler = new MenuRequestHandler(user,this->m_handlerFactory);
		}
		return requestResult;
	}
	catch (std::exception e) {
		ErrorResponse errorResponse(e.what());

		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);
		requestResult.newHandler = new LoginRequestHandler(this->m_handlerFactory);
		return requestResult;
	}


}

RequestResult LoginRequestHandler::signup(const RequestInfo& requestInfo) const
{
	try {

		SignupRequest request = JsonRequestPacketDeserializer<SignupRequest>::deserializeRequest(requestInfo.buffer);
		int status = static_cast<int>(this->m_handlerFactory.getLoginManager().signup(request.getUserRecord()));
		SignupResponse signupResponse(status);
		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(signupResponse);
		requestResult.newHandler = new LoginRequestHandler(this->m_handlerFactory);
		return requestResult;
	}
	catch (const std::runtime_error& e) {
		RequestResult res;
		ErrorResponse errResponse(e.what());
		res.response = JsonResponsePacketSerializer::serializeResponse(errResponse);
		res.newHandler = new LoginRequestHandler(this->m_handlerFactory);
		return res;
	}

	

}


unsigned int  LoginRequestHandler::generateRandomCode(unsigned int digsOfCode) const {
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


RequestResult LoginRequestHandler::sendPasswordResetEmail(const RequestInfo& requestInfo) const
{
	try {
		SendPasswordResetCodeRequest request = JsonRequestPacketDeserializer<SendPasswordResetCodeRequest>::deserializeRequest(requestInfo.buffer);
		unsigned int randomCode = generateRandomCode(CODE_DIGITS);
		unsigned int status = static_cast<int>(this->m_handlerFactory.getLoginManager().sendEmailCode(request.getEmail(), randomCode));
		SendPasswordResetCodeResponse response(
			status,
			randomCode,
			this->m_handlerFactory.getLoginManager().getUsername(request.getEmail())
		);
		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
		requestResult.newHandler = new LoginRequestHandler(this->m_handlerFactory);
		return requestResult;
	}
	catch (const std::runtime_error& e) {
		RequestResult res;
		ErrorResponse errResponse(e.what());
		res.response = JsonResponsePacketSerializer::serializeResponse(errResponse);
		res.newHandler = new LoginRequestHandler(this->m_handlerFactory);
		return res;
	}



}



RequestResult LoginRequestHandler::resetPassword(const RequestInfo& requestInfo) const
{
	try {
		ResetPasswordRequest resetPasswordResponse = JsonRequestPacketDeserializer<ResetPasswordRequest>::deserializeRequest(requestInfo.buffer);

		int status = static_cast<int>(this->m_handlerFactory.getLoginManager().
			resetPassword(resetPasswordResponse.getUsername(), resetPasswordResponse.getNewPassword()));
		ResetPasswordResponse response(status);
		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
		requestResult.newHandler = new LoginRequestHandler(this->m_handlerFactory);
		return requestResult;
	}
	catch (const std::runtime_error& e) {
		RequestResult res;
		ErrorResponse errResponse(e.what());
		res.response = JsonResponsePacketSerializer::serializeResponse(errResponse);
		res.newHandler = new LoginRequestHandler(this->m_handlerFactory);
		return res;
	}



}
