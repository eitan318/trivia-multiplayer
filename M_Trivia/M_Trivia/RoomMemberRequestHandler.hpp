#pragma once
#include "RoomRequestHandler.hpp"

class RoomMemberRequestHandler :  public RoomRequestHandler {
public:
	/**
	 * @brief Constructs a RoomMemeberRequestHandler instance.
	 * @param handlerFactory Reference to the RequestHandlerFactory for creating
	 * other request handlers.
	 */
	RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory,
		LoggedUser loggedUser, Room* room);

	/**
	 * @brief Destructor for RoomMemberRequestHandler.
	 */
	~RoomMemberRequestHandler();

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
	/**
	 * @brief Handles a given request and produces a result.
	 * @param requestInfo The request information to handle.
	 * @return The result request of leaving room, succesfull or not.
	 */
	RequestResult leaveRoomRequest(RequestInfo requestInfo);
};
