#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include "IRequestHandler.h"
#include "RequestResult.hpp"
#include "RequestInfo.hpp"
#include "LoginRequestHandler.h"
#include <iostream>
#include <thread>
#include <string>

#define PORT 5554  ///< The port number for the server to listen on.

/**
 * @class Communicator
 * @brief Handles server-side socket communication and client request management.
 *
 * The Communicator class is responsible for setting up a server socket, accepting new client
 * connections, and delegating request handling to the appropriate IRequestHandler instances.
 */
class Communicator {
private:
    std::map<SOCKET, IRequestHandler*> m_clients;  ///< Map of connected clients and their corresponding IRequestHandler.
    SOCKET m_serverSocket;  ///< The main server socket.
    RequestHandlerFactory& m_handlerFactory;  ///< Reference to the factory for creating request handlers.

    /**
     * @brief Private constructor for singleton pattern.
     *
     * Initializes the Communicator with the specified RequestHandlerFactory.
     *
     * @param handlerFactory Reference to the RequestHandlerFactory.
     */
    Communicator(RequestHandlerFactory& handlerFactory);

    /**
     * @brief Destructor to clean up resources.
     *
     * Closes the server socket and releases associated resources.
     */
    ~Communicator();

    // Disable copy constructor and assignment operator to enforce singleton pattern.
    Communicator(const Communicator&) = delete;
    Communicator& operator=(const Communicator&) = delete;

public:
    /**
     * @brief Retrieves the singleton instance of Communicator.
     *
     * Ensures a single instance of the Communicator exists, initialized with the provided
     * RequestHandlerFactory.
     *
     * @param handlerFactory Reference to the RequestHandlerFactory.
     * @return Reference to the Communicator instance.
     */
    static Communicator& getInstance(RequestHandlerFactory& handlerFactory);

    /**
     * @brief Starts handling client requests.
     *
     * Continuously listens for client connections and delegates incoming requests to
     * appropriate handlers in separate threads.
     */
    void startHandleRequest();

    /**
     * @brief Binds the server socket to the specified port and starts listening for connections.
     *
     * This method sets up the server to accept client connections on the defined PORT.
     *
     * @throws std::runtime_error If socket binding or listening fails.
     */
    void bindAndListen() const;

    /**
     * @brief Handles a new client connection.
     *
     * Assigns an IRequestHandler to the client socket and processes incoming requests.
     *
     * @param clientSocket The socket associated with the new client.
     */
    void handleNewClient(SOCKET clientSocket);
};
