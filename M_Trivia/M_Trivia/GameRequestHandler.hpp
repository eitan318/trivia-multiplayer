#pragma once
#include "IRequestHandler.hpp"
#include "LoggedUser.hpp"
//#include "GameManager.hpp"
#include "RequestHandlerFactory.hpp"

/**
 * @class GameRequestHandler
 * @brief Handles requests related to the game itself.
 *
 * This class manages game-related operations, including getting a question,
 * submitting your answer, getting the game's result and leaving game. It routes
 * requests to the appropriate methods based on their type.
 */
class GameRequestHandler : IRequestHandler {
public:
    /**
     * @brief Checks if a given request is relevant for this handler.
     * @param requestInfo The request information.
     * @return True if the request is relevant, otherwise false.
     */
    bool isRequestRelevant(const RequestInfo& requestInfo) const override;

    /**
     * @brief Handles a request and routes it to the appropriate method.
     * @param requestInfo The request information.
     * @return A RequestResult containing the serialized response and the next
     * handler.
     */
    RequestResult handleRequest(const RequestInfo& requestInfo, SOCKET socket) override;
private:
	LoggedUser m_user;

	RequestHandlerFactory& m_handlerFactory;
};