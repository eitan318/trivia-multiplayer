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
#include "ServerErrorResponse.hpp"
#include "LoginResponse.hpp"
#include "SignupResponse.hpp"
#include "ResetPasswordResponse.hpp"
#include "PasswordCodeResponse.hpp"
#include "JoinRoomResponse.hpp"
#include "LogoutResponse.hpp"
#include "ResetPasswordResponseErrors.hpp"
#include <memory>

#define CODE_DIGITS 6


class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler {
public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactory);
	~LoginRequestHandler();
	bool isRequestRelevant(const RequestInfo&) const override;
	RequestResult handleRequest(const RequestInfo&) const override;
private:
	RequestHandlerFactory& m_handlerFactory;
	RequestResult login(const RequestInfo&) const;
	RequestResult signup(const RequestInfo&) const;
	RequestResult sendPasswordResetEmail(const RequestInfo& requestInfo) const;
	RequestResult resetPassword(const RequestInfo& requestInfo) const;
	unsigned int generateRandomCode(unsigned int digsOfCode) const;

};
