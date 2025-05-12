#include "LoginRequestHandler.h"

#include "RequestsCodes.hpp"
#include "LoginRequest.hpp"
#include "SignupRequest.hpp"
#include "ResetPasswordRequest.hpp"
#include "SendPasswordResetCodeRequest.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "JsonRequestPacketDeserializer.hpp"
#include <random>
#include <cmath>
#include "ServerErrorResponse.hpp"
#include "LoginResponse.hpp"
#include "SignupResponse.hpp"
#include "ResetPasswordResponse.hpp"
#include "PasswordCodeResponse.hpp"
#include "JoinRoomResponse.hpp"
#include "LogoutResponse.hpp"
#include "ResetPasswordResponseErrors.hpp"
#include <memory>


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
	try {
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
			RequestResult requestResult(JsonResponsePacketSerializer::serializeResponse(errorResponse), nullptr);
			return requestResult;
		}
	}
	catch (const std::exception& e) {
		ServerErrorResponse errResponse(e.what());
		RequestResult res(
			JsonResponsePacketSerializer::serializeResponse(errResponse),
			nullptr
		);
		return res;
	}

}

RequestResult LoginRequestHandler::login(const RequestInfo& requestInfo) const
{

	LoginRequest request = JsonRequestPacketDeserializer<LoginRequest>::deserializeRequest(requestInfo.buffer);

	auto errors = LoginResponseErrors(
		this->m_handlerFactory.getLoginManager().login(request.getUsername(), request.getPassword()));
	LoginResponse loginResponse(&errors);

	auto response = JsonResponsePacketSerializer::serializeResponse(loginResponse);
	std::unique_ptr<IRequestHandler> newHandler;
	LoggedUser user(request.getUsername());
	if (errors.statusCode != 0) {
		newHandler = this->m_handlerFactory.createLoginRequestHandler();
	}
	else {
		newHandler = this->m_handlerFactory.createMenuRequestHandler(user);
	}
	return RequestResult(response, std::move(newHandler));

}

RequestResult LoginRequestHandler::signup(const RequestInfo& requestInfo) const
{
	SignupRequest request = JsonRequestPacketDeserializer<SignupRequest>::deserializeRequest(requestInfo.buffer);
	auto errors = SignupResponseErrors(
		this->m_handlerFactory.getLoginManager().signup(request.getUserRecord()));

	SignupResponse signupResponse(&errors);
	RequestResult requestResult(
		JsonResponsePacketSerializer::serializeResponse(signupResponse),
		this->m_handlerFactory.createLoginRequestHandler()
	);
	return requestResult;
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
	SendPasswordResetCodeRequest request = JsonRequestPacketDeserializer<SendPasswordResetCodeRequest>::deserializeRequest(requestInfo.buffer);
	unsigned int randomCode = generateRandomCode(CODE_DIGITS);
	auto errors = PasswordCodeResponseErrors(
		this->m_handlerFactory.getLoginManager().sendEmailCode(request.getEmail(), randomCode));

	std::string username = errors.statusCode == 0 ?
		this->m_handlerFactory.getLoginManager().getUsername(request.getEmail()) :
		"Error occured: No username";


	PasswordCodeResponse response(
		&errors,
		randomCode,
		username
	);

	RequestResult requestResult(
		JsonResponsePacketSerializer::serializeResponse(response),
		this->m_handlerFactory.createLoginRequestHandler()
	);
	return requestResult;
}



RequestResult LoginRequestHandler::resetPassword(const RequestInfo& requestInfo) const
{
	ResetPasswordRequest resetPasswordRequest = JsonRequestPacketDeserializer<ResetPasswordRequest>::deserializeRequest(requestInfo.buffer);

	ResetPasswordResponseErrors errors =
		ResetPasswordResponseErrors(
			this->m_handlerFactory.getLoginManager().resetPassword(
				resetPasswordRequest.getUsername(),
				resetPasswordRequest.getNewPassword()
			)
		);

	ResetPasswordResponse response(&errors);
	RequestResult requestResult(
		JsonResponsePacketSerializer::serializeResponse(response),
		this->m_handlerFactory.createLoginRequestHandler()
	);
	return requestResult;

}
