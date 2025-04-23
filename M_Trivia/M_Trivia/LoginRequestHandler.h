#pragma once
#include "IRequestHandler.h"
#include "MenuRequestHandler.h"
#include "Requests.hpp"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "Responses.hpp"
#include "RequestHandlerFactory.h"
#include <random>
#include <cmath>

#define CODE_DIGITS 6 ///< Number of digits in the randomly generated code.

/**
 * @brief Handles login-related requests such as login, signup, password reset, and sending reset codes.
 */
class LoginRequestHandler : public IRequestHandler {
public:
    /**
     * @brief Constructs a LoginRequestHandler instance.
     * @param handlerFactory Reference to the RequestHandlerFactory.
     */
    LoginRequestHandler(RequestHandlerFactory& handlerFactory);

    /**
     * @brief Destructor for LoginRequestHandler.
     */
    ~LoginRequestHandler();

    /**
     * @brief Determines if the given request is relevant to this handler.
     * @param requestInfo Information about the request.
     * @return True if the request is relevant, false otherwise.
     */
    bool isRequestRelevant(const RequestInfo& requestInfo) const;

    /**
     * @brief Handles a given request.
     * @param requestInfo Information about the request.
     * @return The result of handling the request, including the response and the next handler.
     */
    RequestResult handleRequest(const RequestInfo& requestInfo) const;

private:
    RequestHandlerFactory& m_handlerFactory; ///< Reference to the factory for creating handlers.

    /**
     * @brief Handles login requests.
     * @param requestInfo Information about the login request.
     * @return The result of the login request, including the response and the next handler.
     */
    RequestResult login(const RequestInfo& requestInfo) const;

    /**
     * @brief Handles signup requests.
     * @param requestInfo Information about the signup request.
     * @return The result of the signup request, including the response and the next handler.
     */
    RequestResult signup(const RequestInfo& requestInfo) const;

    /**
     * @brief Handles requests to send a password reset email.
     * @param requestInfo Information about the password reset email request.
     * @return The result of the request, including the response and the next handler.
     */
    RequestResult sendPasswordResetEmail(const RequestInfo& requestInfo) const;

    /**
     * @brief Handles requests to reset a password.
     * @param requestInfo Information about the password reset request.
     * @return The result of the request, including the response and the next handler.
     */
    RequestResult resetPassword(const RequestInfo& requestInfo) const;

    /**
     * @brief Generates a random numeric code with the specified number of digits.
     * @param digsOfCode Number of digits in the code.
     * @return A randomly generated code.
     * @throws std::invalid_argument if digsOfCode is 0.
     */
    unsigned int generateRandomCode(unsigned int digsOfCode) const;
};
