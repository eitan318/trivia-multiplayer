/**
 * @file LoginRequestHandler.h
 * @brief Declaration of the LoginRequestHandler class responsible for handling
 * login-related requests.
 */

#pragma once
#include "IRequestHandler.hpp"
#include "RequestHandlerFactory.hpp"
#include "RequestInfo.hpp"
#include "RequestResult.hpp"
#include <string>
#include <WinSock2.h>

#define CODE_DIGITS 6

class RequestHandlerFactory;

/**
 * @class LoginRequestHandler
 * @brief Handles requests related to user login, signup, and password
 * management.
 */
class LoginRequestHandler : public IRequestHandler {
public:
    /**
     * @brief Constructs a LoginRequestHandler instance.
     * @param handlerFactory Reference to the RequestHandlerFactory for creating
     * other request handlers.
     */
    LoginRequestHandler(RequestHandlerFactory& handlerFactory);

    /**
     * @brief Destructor for LoginRequestHandler.
     */
    ~LoginRequestHandler();

    /**
     * @brief Checks if a given request is relevant for this handler.
     * @param requestInfo The request information to be checked.
     * @return True if the request is relevant, false otherwise.
     */
    bool isRequestRelevant(const RequestInfo& requestInfo) const override;

    /**
     * @brief Handles a given request and produces a result.
     * @param requestInfo The request information to handle.
     * @return The result of handling the request.
     */
    RequestResult handleRequest(const RequestInfo& requestInfo, SOCKET socket) override;

private:
    RequestHandlerFactory
        & m_handlerFactory; /**< Reference to the request handler factory. */

    /**
     * @brief Handles login requests.
     * @param requestInfo The request information for login.
     * @return The result of the login process.
     */
    RequestResult login(const RequestInfo& requestInfo, SOCKET) const;

    /**
     * @brief Handles signup requests.
     * @param requestInfo The request information for signup.
     * @return The result of the signup process.
     */
    RequestResult signup(const RequestInfo& requestInfo) const;

    /**
     * @brief Sends a password reset email.
     * @param requestInfo The request information containing the email details.
     * @return The result of sending the email.
     */
    RequestResult sendPasswordResetEmail(const RequestInfo& requestInfo);

    /**
     * @brief Handles password reset requests.
     * @param requestInfo The request information for resetting the password.
     * @return The result of the password reset process.
     */
    RequestResult resetPassword(const RequestInfo& requestInfo) const;
    /**
     * @brief Handles password reset code verification requests.
     * @param requestInfo The request information .
     * @return The result of the password reset process.
     */
    RequestResult verifyResetPasswordCode(const RequestInfo& requestInfo);

    /**
     * @brief Generates a random code of specified digit length.
     * @param digsOfCode The number of digits in the random code.
     * @return The generated random code.
     */
    unsigned int generateRandomCode(unsigned int digsOfCode) const;

    /**
     * @brief Generates a random verification tocken of const digit length.
     * @return The generated random verification tocken.
     */
    std::string generateVerificationTocken() const;
};
