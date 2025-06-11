#pragma once
#include "IRequestHandler.hpp"
#include "LoggedUser.hpp"
#include "Question.hpp"
#include "GameManager.hpp"
#include "RequestHandlerFactory.hpp"

/**
 * @class GameRequestHandler
 * @brief Handles requests related to the game itself.
 *
 * This class manages game-related operations, including getting a question,
 * submitting your answer, getting the game's result and leaving game. It routes
 * requests to the appropriate methods based on their type.
 */
class GameRequestHandler : public IRequestHandler {
public:
    /**
     * @brief Constructor for the GameRequestHandler class.
     * @param user The currently logged-in user.
     * @param handlerFactory The factory for creating other request handlers.
     */
    GameRequestHandler(const LoggedUser& user,
        RequestHandlerFactory& handlerFactory,Room* room); 

    /**
     * @brief Default destructor.
     */
    ~GameRequestHandler();
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
    Room* m_room;
    RequestHandlerFactory& m_handlerFactory;
    GameManager& m_gameManager;
    std::shared_ptr<Game> m_game;

    /**
     * @brief gets a the current question and sends to clients.
     * @param requestInfo The request information.
     * @return A RequestResult containing the serialized response and the next
     * handler.
     */
    RequestResult getQuestion(RequestInfo requestInfo);

    /**
     * @brief submitting the answers for the players.
     * @param requestInfo The request information.
     * @return A RequestResult containing the serialized response and the next
     * handler.
     */
    RequestResult submitAnswer(RequestInfo requestInfo);

    /**
     * @brief sends Game's Result.
     * @param requestInfo The request information.
     * @return A RequestResult containing the serialized response and the next
     * handler.
     */
    RequestResult getGameResults(RequestInfo requestInfo);

    /**
     * @brief removes the player who requested to leave the game.
     * @param requestInfo The request information.
     * @return A RequestResult containing the serialized response and the next
     * handler.
     */
    RequestResult leaveGame(RequestInfo requestInfo);
};