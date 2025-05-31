#include "RoomRequestHandler.hpp"

class RoomAdminRequestHandler : RoomRequestHandler {
public:
	/**
	 * @brief Constructs a RoomAdminRequestHandler instance.
	 * @param handlerFactory Reference to the RequestHandlerFactory for creating
	 * other request handlers.
	 */
	RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory,
		LoggedUser loggedUser, Room* room);

	/**
	 * @brief Destructor for RoomAdminRequestHandler.
	 */
	~RoomAdminRequestHandler();

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
	RequestResult closeRoom(const RequestInfo& requestInfo);
	RequestResult startGame(const RequestInfo& requestInfo);

};
