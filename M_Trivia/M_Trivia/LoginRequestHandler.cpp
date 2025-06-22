#include "LoginRequestHandler.hpp"
#include "JsonRequestPacketDeserializer.hpp"
#include "JsonResponsePacketSerializer.hpp"
#include "Requests.hpp"
#include "RequestInfo.hpp"
#include "RequestResult.hpp"
#include "RequestsCodes.hpp"
#include "ResetPasswordResponseErrors.hpp"
#include <cmath>
#include <memory>
#include <random>
#include <string>
#include "MyException.hpp"
#include "Response.hpp"

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
LoginRequestHandler::handleRequest(const RequestInfo& requestInfo) {
    switch (static_cast<RequestCodes>(requestInfo.code)) {
    case RequestCodes::LoginRequest:
        return login(requestInfo);
    case RequestCodes::SignupRequest:
        return signup(requestInfo);
    case RequestCodes::SendPasswordResetCodeRequest:
        return sendPasswordResetEmail(requestInfo);
    case RequestCodes::VerifyPasswordResetCodeRequest:
        return verifyResetPasswordCode(requestInfo);
    case RequestCodes::ResetPasswordRequest:
        return resetPassword(requestInfo);
    default:
        ServerErrorResponse errorResponse(GENERAL_SUCCESS_RESPONSE_STATUS, "Invalid msg code.");
        RequestResult requestResult(
            JsonResponsePacketSerializer::serializeResponse(errorResponse),
            nullptr);
        return requestResult;
    }
}

void LoginRequestHandler::Cleanup()
{
}

RequestResult LoginRequestHandler::login(const RequestInfo& requestInfo) const {

    LoginRequest request =
        JsonRequestPacketDeserializer::deserializeRequest<LoginRequest>(
            requestInfo.buffer);


    auto errors =
        this->m_handlerFactory.getLoginManager().login(
            request.username, request.password);
    LoginResponse loginResponse(std::make_unique<LoginResponseErrors>(errors));

    auto response =
        JsonResponsePacketSerializer::serializeResponse(loginResponse);
    std::shared_ptr<IRequestHandler> newHandler;
    LoggedUser user(request.username);
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
        JsonRequestPacketDeserializer::deserializeRequest<SignupRequest>(
            requestInfo.buffer);
    auto errors = 
        this->m_handlerFactory.getLoginManager().signup(request.userRecord);

    SignupResponse signupResponse(std::make_unique<SignupResponseErrors>(errors));
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
    SendPasswordResetCodeRequest request = JsonRequestPacketDeserializer::deserializeRequest<
        SendPasswordResetCodeRequest>(requestInfo.buffer);
    unsigned int randomCode = generateRandomCode(CODE_DIGITS);
    auto errors = this->m_handlerFactory.getLoginManager().sendEmailCode(request.email, randomCode);

    PasswordCodeResponse response(std::make_unique<GeneralResponseErrors>(errors));

    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(response),
        this->m_handlerFactory.createLoginRequestHandler());
    return requestResult;
}

RequestResult
LoginRequestHandler::resetPassword(const RequestInfo& requestInfo) const {
    ResetPasswordRequest resetPasswordRequest =
        JsonRequestPacketDeserializer::deserializeRequest<ResetPasswordRequest>(
            requestInfo.buffer);


    ResetPasswordResponseErrors errors =
        this->m_handlerFactory.getLoginManager().resetPassword(
            resetPasswordRequest.email,
            resetPasswordRequest.newPassword,
            resetPasswordRequest.resetPasswordTocken);

    ResetPasswordResponse response(std::make_unique<ResetPasswordResponseErrors>(errors));
    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(response),
        this->m_handlerFactory.createLoginRequestHandler());
    return requestResult;
}

RequestResult
LoginRequestHandler::verifyResetPasswordCode(const RequestInfo& requestInfo) {
    VerifyPasswordResetCodeRequest verifyPasswordResetCodeRequest =
        JsonRequestPacketDeserializer::
        deserializeRequest<VerifyPasswordResetCodeRequest>(requestInfo.buffer);

    std::string verificationTocken = generateVerificationTocken();
    GeneralResponseErrors errors =
        this->m_handlerFactory.getLoginManager().verifyResetPasswordCode(
            verifyPasswordResetCodeRequest.resetCode, verificationTocken);

    VerifyPasswordResetCodeResponse response(std::make_unique<GeneralResponseErrors>(errors), verificationTocken);
    RequestResult requestResult(
        JsonResponsePacketSerializer::serializeResponse(response),
        this->m_handlerFactory.createLoginRequestHandler());

    return requestResult;
}
