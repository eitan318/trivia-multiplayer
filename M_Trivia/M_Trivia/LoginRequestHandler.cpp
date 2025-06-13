#include "LoginRequestHandler.hpp"
#include "JoinRoomResponse.hpp"
#include "JsonRequestPacketDeserializer.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "LoginRequest.hpp"
#include "LoginResponse.hpp"
#include "LogoutResponse.hpp"
#include "PasswordCodeResponse.hpp"
#include "RequestInfo.hpp"
#include "RequestResult.hpp"
#include "RequestsCodes.hpp"
#include "ResetPasswordRequest.hpp"
#include "ResetPasswordResponse.hpp"
#include "ResetPasswordResponseErrors.hpp"
#include "SendPasswordResetCodeRequest.hpp"
#include "ServerErrorResponse.hpp"
#include "SignupRequest.hpp"
#include "SignupResponse.hpp"
#include "VerifyPasswordResetCodeRequest.hpp"
#include "VerifyPasswordResetCodeResponse.hpp"
#include <cmath>
#include <memory>
#include <random>
#include <string>
#include "MyException.hpp"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory)
    : m_handlerFactory(handlerFactory) {
}

LoginRequestHandler::~LoginRequestHandler() {}

bool LoginRequestHandler::isRequestRelevant(
    const RequestInfo& requestInfo) const {
    switch (static_cast<RequestCodes>(requestInfo.code)) {
    case RequestCodes::LoginRequest:
    case RequestCodes::SignupRequest:
    case RequestCodes::SendPasswordResetCodeRequest:
    case RequestCodes::ResetPasswordRequest:
    case RequestCodes::VerifyPasswordResetCodeRequest:
        return true;
    default:
        return false;
    }
}

RequestResult
LoginRequestHandler::handleRequest(const RequestInfo& requestInfo, SOCKET socket) {
    try {
        switch (static_cast<RequestCodes>(requestInfo.code)) {
        case RequestCodes::LoginRequest:
            return login(requestInfo, socket);
        case RequestCodes::SignupRequest:
            return signup(requestInfo);
        case RequestCodes::SendPasswordResetCodeRequest:
            return sendPasswordResetEmail(requestInfo);
        case RequestCodes::VerifyPasswordResetCodeRequest:
            return verifyResetPasswordCode(requestInfo);
        case RequestCodes::ResetPasswordRequest:
            return resetPassword(requestInfo);
        default:
            ServerErrorResponse errorResponse("Invalid msg code.");
            RequestResult requestResult(
                JsonResponsePacketSerializer::serializeResponse(errorResponse),
                nullptr);
            return requestResult;
        }
    }
    catch (const std::exception& e) {
        ServerErrorResponse errResponse(e.what());
        RequestResult res(
            JsonResponsePacketSerializer::serializeResponse(errResponse), nullptr);
        return res;
    }
}

RequestResult LoginRequestHandler::login(const RequestInfo& requestInfo, SOCKET socket) const {

    LoginRequest request =
        JsonRequestPacketDeserializer<LoginRequest>::deserializeRequest(
            requestInfo.buffer);

    auto errors =
        this->m_handlerFactory.getLoginManager().login(
            request.getUsername(), request.getPassword(), socket);
    LoginResponse loginResponse(&errors);

    auto response =
        JsonResponsePacketSerializer::serializeResponse(loginResponse);
    std::shared_ptr<IRequestHandler> newHandler;
    LoggedUser user(request.getUsername());
    if (errors.statusCode() != 0) {
        newHandler = this->m_handlerFactory.createLoginRequestHandler();
    }
    else {
        newHandler = this->m_handlerFactory.createMenuRequestHandler(user);
    }
    return RequestResult(response, std::move(newHandler));
}

RequestResult
LoginRequestHandler::signup(const RequestInfo& requestInfo) const {
    SignupRequest request =
        JsonRequestPacketDeserializer<SignupRequest>::deserializeRequest(
            requestInfo.buffer);
    auto errors = 
        this->m_handlerFactory.getLoginManager().signup(request.getUserRecord());

    SignupResponse signupResponse(&errors);
    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(signupResponse),
        this->m_handlerFactory.createLoginRequestHandler());
    return requestResult;
}

unsigned int
LoginRequestHandler::generateRandomCode(unsigned int digsOfCode) const {
    if (digsOfCode == 0) {
        throw std::invalid_argument("Number of digits must be greater than 0");
    }

    unsigned int lowerBound =
        static_cast<unsigned int>(std::pow(10, digsOfCode - 1));
    unsigned int upperBound =
        static_cast<unsigned int>(std::pow(10, digsOfCode)) - 1;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(lowerBound, upperBound);

    return dist(gen);
}

std::string LoginRequestHandler::generateVerificationTocken() const {
    unsigned int verificationTockenNum = this->generateRandomCode(6);
    std::string verificationTocken = std::to_string(verificationTockenNum);
    return verificationTocken;
}

RequestResult
LoginRequestHandler::sendPasswordResetEmail(const RequestInfo& requestInfo) {
    SendPasswordResetCodeRequest request = JsonRequestPacketDeserializer<
        SendPasswordResetCodeRequest>::deserializeRequest(requestInfo.buffer);
    unsigned int randomCode = generateRandomCode(CODE_DIGITS);
    auto errors = this->m_handlerFactory.getLoginManager().sendEmailCode(request.getEmail(), randomCode);

    PasswordCodeResponse response(&errors);

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(response),
        this->m_handlerFactory.createLoginRequestHandler());
    return requestResult;
}

RequestResult
LoginRequestHandler::resetPassword(const RequestInfo& requestInfo) const {
    ResetPasswordRequest resetPasswordRequest =
        JsonRequestPacketDeserializer<ResetPasswordRequest>::deserializeRequest(
            requestInfo.buffer);


    ResetPasswordResponseErrors errors =
        this->m_handlerFactory.getLoginManager().resetPassword(
            resetPasswordRequest.getEmail(),
            resetPasswordRequest.getNewPassword(),
            resetPasswordRequest.getResetPasswordTocken());

    ResetPasswordResponse response(&errors);
    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(response),
        this->m_handlerFactory.createLoginRequestHandler());
    return requestResult;
}

RequestResult
LoginRequestHandler::verifyResetPasswordCode(const RequestInfo& requestInfo) {
    VerifyPasswordResetCodeRequest verifyPasswordResetCodeRequest =
        JsonRequestPacketDeserializer<VerifyPasswordResetCodeRequest>::
        deserializeRequest(requestInfo.buffer);

    std::string verificationTocken = generateVerificationTocken();
    VerifyPasswordResetCodeResponseErrors errors =
        this->m_handlerFactory.getLoginManager().verifyResetPasswordCode(
            verifyPasswordResetCodeRequest.getCodeFromClient(), verificationTocken);



    VerifyPasswordResetCodeResponse response(&errors, verificationTocken);
    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(response),
        this->m_handlerFactory.createLoginRequestHandler());

    return requestResult;
}
