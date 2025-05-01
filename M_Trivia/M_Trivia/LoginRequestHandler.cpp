#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
{
}

LoginRequestHandler::~LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	switch (static_cast<RequestCodes>(requestInfo.code)) {
	case RequestCodes::LoginRequest:
	case RequestCodes::SignupRequest:
	case RequestCodes::SendPasswordResetCodeRequest:
	case RequestCodes::ResetPasswordRequest:
		return true;
	default:
		return false;
	}
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	switch (static_cast<RequestCodes>(requestInfo.code)) {
	case RequestCodes::LoginRequest:
		return login(requestInfo);
	case RequestCodes::SignupRequest:
		return signup(requestInfo);
	case RequestCodes::SendPasswordResetCodeRequest:
		return sendPasswordResetEmail(requestInfo);
	case RequestCodes::ResetPasswordRequest:
		return resetPassword(requestInfo);
	default:
		ServerErrorResponse errorResponse("Invalid msg code.");
		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);
		requestResult.newHandler = nullptr;
		return requestResult;
	}
}

RequestResult LoginRequestHandler::login(const RequestInfo& requestInfo) const
{

	try {
		LoginRequest request = JsonRequestPacketDeserializer<LoginRequest>::deserializeRequest(requestInfo.buffer);

		auto errors = std::make_shared<LoginResponseErrors>(
			this->m_handlerFactory.getLoginManager().login(request.getUsername(), request.getPassword()));
		LoginResponse loginResponse(errors);
		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(loginResponse);
		LoggedUser user;
		user.m_username = request.getUsername();
		if (errors->statusCode != 0) {
			requestResult.newHandler = std::make_unique<LoginRequestHandler>(this->m_handlerFactory);
		}
		else {
			requestResult.newHandler = std::make_unique<MenuRequestHandler>(user, this->m_handlerFactory);
		}
		return requestResult;
	}
	catch (std::exception e) {
		ServerErrorResponse errorResponse(e.what());

		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);
		requestResult.newHandler  = std::make_unique<LoginRequestHandler>(this->m_handlerFactory);
		return requestResult;
	}


}

RequestResult LoginRequestHandler::signup(const RequestInfo& requestInfo) const
{
	try {

		SignupRequest request = JsonRequestPacketDeserializer<SignupRequest>::deserializeRequest(requestInfo.buffer);
		auto errors = std::make_shared<SignupResponseErrors>(
			this->m_handlerFactory.getLoginManager().signup(request.getUserRecord()));

		SignupResponse signupResponse(errors);
		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(signupResponse);
		requestResult.newHandler = std::make_unique<LoginRequestHandler>(this->m_handlerFactory);
		return requestResult;
	}
	catch (const std::runtime_error& e) {
		RequestResult res;
		ServerErrorResponse errResponse(e.what());
		res.response = JsonResponsePacketSerializer::serializeResponse(errResponse);
		res.newHandler = std::make_unique<LoginRequestHandler>(this->m_handlerFactory);
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
		auto errors = std::make_shared<PasswordCodeResponseErrors>(
			this->m_handlerFactory.getLoginManager().sendEmailCode(request.getEmail(), randomCode));

		std::string username = errors->statusCode == 0 ?
			this->m_handlerFactory.getLoginManager().getUsername(request.getEmail()) :
			"Error occured: No username";


		PasswordCodeResponse response(
			errors,
			randomCode,
			username
		);

		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
		requestResult.newHandler = std::make_unique<LoginRequestHandler>(this->m_handlerFactory);
		return requestResult;
	}
	catch (const std::runtime_error& e) {
		RequestResult res;
		ServerErrorResponse errResponse(e.what());
		res.response = JsonResponsePacketSerializer::serializeResponse(errResponse);
		res.newHandler = std::make_unique<LoginRequestHandler>(this->m_handlerFactory);
		return res;
	}



}



RequestResult LoginRequestHandler::resetPassword(const RequestInfo& requestInfo) const
{
	try {
		ResetPasswordRequest resetPasswordRequest = JsonRequestPacketDeserializer<ResetPasswordRequest>::deserializeRequest(requestInfo.buffer);

		std::shared_ptr<ResetPasswordResponseErrors> errors =
			std::make_shared<ResetPasswordResponseErrors>(
				this->m_handlerFactory.getLoginManager().resetPassword(
					resetPasswordRequest.getUsername(),
					resetPasswordRequest.getNewPassword()
				)
			);

		ResetPasswordResponse response(errors);
		RequestResult requestResult;
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
		requestResult.newHandler = std::make_unique<LoginRequestHandler>(this->m_handlerFactory);;
		return requestResult;
	}
	catch (const std::runtime_error& e) {
		RequestResult res;
		ServerErrorResponse errResponse(e.what());
		res.response = JsonResponsePacketSerializer::serializeResponse(errResponse);
		res.newHandler = std::make_unique<LoginRequestHandler>(this->m_handlerFactory);
		return res;
	}



}
