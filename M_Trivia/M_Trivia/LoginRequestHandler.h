#pragma once
#include "IRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RequestsCodes.hpp"
#include "LoginRequest.hpp"
#include "SignupRequest.hpp"
#include "ResetPasswordRequest.hpp"
#include "SendPasswordResetCodeRequest.hpp"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequestHandlerFactory.h"
#include <random>
#include <cmath>
#include "ErrorResponse.hpp"
#include "LoginResponse.hpp"
#include "SignupResponse.hpp"
#include "ResetPasswordResponse.hpp"
#include "SendPasswordResetCodeResponse.hpp"
#include "JoinRoomResponse.hpp"
#include "LogoutResponse.hpp"

#define CODE_DIGITS 6


class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler {
public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactory);
	~LoginRequestHandler();
	bool isRequestRelevant(const RequestInfo&) const;
	RequestResult handleRequest(const RequestInfo&) const;
private:
	RequestHandlerFactory& m_handlerFactory;
	RequestResult login(const RequestInfo&) const;
	RequestResult signup(const RequestInfo&) const;
	RequestResult sendPasswordResetEmail(const RequestInfo& requestInfo) const;
	RequestResult resetPassword(const RequestInfo& requestInfo) const;
	unsigned int generateRandomCode(unsigned int digsOfCode) const;

};
