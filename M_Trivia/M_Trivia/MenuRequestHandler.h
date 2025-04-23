#pragma once
#include "LoggedUser.h"
#include "Requests.hpp"
#include "RequestHandlerFactory.h"
#include "JoinRoomResponseStatus.h"
#include "CreateRoomResponseStatus.h"
#include "Responses.hpp"

class RequestHandlerFactory;

/**
 * @class MenuRequestHandler
 * @brief Handles requests related to the main menu operations.
 *
 * This class manages menu-related operations, including creating and joining rooms,
 * retrieving personal statistics, and managing high scores. It routes requests to the
 * appropriate methods based on their type.
 */
class MenuRequestHandler : public IRequestHandler {
private:
    LoggedUser& m_user; ///< The currently logged-in user.
    RequestHandlerFactory& m_handlerFactory; ///< Factory to create other request handlers.

    /**
     * @brief Handles the user sign-out request.
     * @param requestInfo The request information containing details about the sign-out request.
     * @return A RequestResult with the serialized response and the next handler.
     */
    RequestResult signout(const RequestInfo& requestInfo) const;

    /**
     * @brief Retrieves a list of available rooms.
     * @param requestInfo The request information.
     * @return A RequestResult containing the serialized response with room data and the next handler.
     */
    RequestResult getRooms(const RequestInfo& requestInfo) const;

    /**
     * @brief Gets the list of players in a specific room.
     * @param requestInfo The request information, including the room ID.
     * @return A RequestResult containing the serialized response with player data and the next handler.
     */
    RequestResult getPlayersInRoom(const RequestInfo& requestInfo) const;

    /**
     * @brief Retrieves the personal statistics of the logged-in user.
     * @param requestInfo The request information.
     * @return A RequestResult with the user's statistics and the next handler.
     */
    RequestResult getPersonalStats(const RequestInfo& requestInfo) const;

    /**
     * @brief Retrieves the high scores from the statistics manager.
     * @param requestInfo The request information, including optional filters such as top player limits.
     * @return A RequestResult containing the high scores and the next handler.
     */
    RequestResult getHighScore(const RequestInfo& requestInfo) const;

    /**
     * @brief Handles a request to join an existing room.
     * @param requestInfo The request information, including the room ID.
     * @return A RequestResult indicating the success or failure of joining the room and the next handler.
     */
    RequestResult joinRoom(const RequestInfo& requestInfo) const;

    /**
     * @brief Handles a request to create a new room.
     * @param requestInfo The request information, including room configuration details.
     * @return A RequestResult indicating the success or failure of room creation and the next handler.
     */
    RequestResult createRoom(const RequestInfo& requestInfo) const;

public:
    /**
     * @brief Constructor for the MenuRequestHandler class.
     * @param user The currently logged-in user.
     * @param handlerFactory The factory for creating other request handlers.
     */
    MenuRequestHandler(LoggedUser& user, RequestHandlerFactory& handlerFactory);

    /**
     * @brief Checks if a given request is relevant for this handler.
     * @param requestInfo The request information.
     * @return True if the request is relevant, otherwise false.
     */
    bool isRequestRelevant(const RequestInfo& requestInfo) const;

    /**
     * @brief Handles a request and routes it to the appropriate method.
     * @param requestInfo The request information.
     * @return A RequestResult containing the serialized response and the next handler.
     */
    RequestResult handleRequest(const RequestInfo& requestInfo) const;
};
