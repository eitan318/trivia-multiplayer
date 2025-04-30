#pragma once
#include "Communicator.h"
#include <thread>
#include <string>
#include <iostream>
#include "IDatabase.h"
#include "RequestHandlerFactory.h"
#include "SqliteDatabase.h"

/**
 * @class Server
 * @brief Singleton class that manages the server's operation, including database access, request handling, and communication.
 */
class Server {
private:
    IDatabase &m_database;                   
    RequestHandlerFactory& m_handlerFactory; 
    Communicator& m_communicator;            

    /**
     * @brief Private constructor to enforce the singleton pattern.
     */
    Server();

    /**
     * @brief Destructor for cleaning up server resources.
     */
    ~Server();

    /**
     * @brief Deleted copy constructor to prevent copying.
     */
    Server(const Server&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent assignment.
     */
    Server& operator=(const Server&) = delete;

public:
    /**
     * @brief Retrieves the singleton instance of the server.
     * @return A reference to the single Server instance.
     */
    static Server& getInstance();

    /**
     * @brief Starts the server's operation, including handling requests and client communication.
     */
    void run() const;
};
