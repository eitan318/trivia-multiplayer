#include "Communicator.hpp"

#include "JsonResponsePacketSerializer.hpp"
#include "LoginRequestHandler.hpp"
#include "RequestInfo.hpp"
#include "RequestResult.hpp"
#include "ServerErrorResponse.hpp"
#include "SocketService.hpp"
#include <Windows.h>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

Communicator::Communicator(RequestHandlerFactory &handlerFactory) : m_handlerFactory(handlerFactory)
{
    // This server uses TCP. Hence, SOCK_STREAM & IPPROTO_TCP
    // If the server uses UDP, use SOCK_DGRAM & IPPROTO_UDP
    this->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (this->m_serverSocket == INVALID_SOCKET)
    {
        int errorCode = WSAGetLastError();
        std::cerr << "socket() failed with error: " << errorCode << std::endl;
        throw std::runtime_error(std::string(__FUNCTION__) + " - socket() failed with error " +
                                 std::to_string(errorCode));
    }
}

Communicator::~Communicator()
{
    try
    {
        // Close all client sockets
        for (const auto &[sock, handler] : this->m_clients)
        {
            if (sock != INVALID_SOCKET)
            {
                closesocket(sock);
            }
        }

        // Close the server socket
        closesocket(this->m_serverSocket);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in destructor: " << e.what() << std::endl;
    }
}

Communicator &Communicator::getInstance(RequestHandlerFactory &handlerFactory)
{
    static Communicator instance(handlerFactory);
    return instance;
}

void Communicator::startHandleRequest()
{
    while (true)
    {
        SOCKET client_socket = accept(this->m_serverSocket, NULL, NULL);
        if (client_socket == INVALID_SOCKET)
        {
            throw std::exception(__FUNCTION__);
        }
        try
        {
            std::thread t_client(&Communicator::handleNewClient, this, client_socket);
            t_client.detach();
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: accepting client" << e.what() << "\n";
            closesocket(client_socket);
        }
    }
}

void Communicator::bindAndListen() const
{
    const int port = PORT;

    struct sockaddr_in sa = {0};

    sa.sin_port = htons(port);       // Port that server will listen on
    sa.sin_family = AF_INET;         // Must be AF_INET
    sa.sin_addr.s_addr = INADDR_ANY; // "INADDR_ANY" for any available IPs

    // Connects between the socket and the configuration (port, etc.)
    if (bind(this->m_serverSocket, (struct sockaddr *)&sa, sizeof(sa)) == SOCKET_ERROR)
    {
        int errorCode = WSAGetLastError();
        std::cerr << "bind() failed with error: " << errorCode << std::endl;
        throw std::runtime_error(std::string(__FUNCTION__) + " - bind() failed with error " +
                                 std::to_string(errorCode));
    }

    // Start listening for incoming requests from clients
    if (listen(this->m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        int errorCode = WSAGetLastError();
        std::cerr << "bind() failed with error: " << errorCode << std::endl;
        throw std::runtime_error(std::string(__FUNCTION__) + " - listen() failed with error " +
                                 std::to_string(errorCode));
    }

    std::cout << "Listening on port " << port << std::endl;
}

void Communicator::handleNewClient(SOCKET sock)
{
    std::cout << "Client " << sock << " accepted." << std::endl;

    // Create a shared_ptr for the initial handler
    std::shared_ptr<IRequestHandler> handler = this->m_handlerFactory.createLoginRequestHandler();

    {
        std::lock_guard<std::mutex> lock(m_clientsMtx);
        this->m_clients.insert({sock, handler}); // Add shared_ptr to map
    }

    while (handler != nullptr)
    {
        int msgLen;
        std::string msgStr;
        unsigned int requestCode;
        try
        {
            requestCode = SocketService::getLittleEndianIntFromSocket(sock, 1);
            msgLen = SocketService::getLittleEndianIntFromSocket(sock, sizeof(int));
            msgStr = SocketService::getStringPartFromSocket(sock, msgLen);
        }
        catch (std::exception &e)
        {
            std::cerr << "Client " << sock << " probably exited ungracefully." << std::endl;
            handler->Cleanup();
            break;
        }
        time_t requestRecievalTime = time(nullptr);
        std::cout << "Received: " << "("<< requestCode << ")" << msgStr << std::endl;
        std::vector<char> requestBuffer(msgStr.begin(), msgStr.end());

        RequestInfo requestInfo(requestCode, requestRecievalTime, requestBuffer);
        RequestResult requestResult;
        if (handler->isRequestRelevant(requestInfo))
        {
            try {
                requestResult = handler->handleRequest(requestInfo);
            }
            catch (const std::exception& e) {
                ServerErrorResponse errResponse(e.what());
                RequestResult res(
                    JsonResponsePacketSerializer::serializeResponse(errResponse), nullptr);
                requestResult = res;
            }
        }
        else
        {
            ServerErrorResponse errorResponse("Invalid msg code.");
            requestResult = RequestResult(JsonResponsePacketSerializer::serializeResponse(errorResponse), nullptr);
        }

        // Update handler if it has changed
        if (requestResult.newHandler)
        {
            handler = requestResult.newHandler; // Update the handler
            std::lock_guard<std::mutex> lock(m_clientsMtx);
            this->m_clients.at(sock) = requestResult.newHandler; // Update in map
        }

        // Send response back to the client
        SocketService::sendData(sock, requestResult.response);
        std::cout << "Sent: " << (int)requestResult.response[0] << std::string(requestResult.response.begin(), requestResult.response.end()) << std::endl;
    }

    closesocket(sock);

    // Cleanup on client disconnect or error
    {
        std::lock_guard<std::mutex> lock(m_clientsMtx);
        this->m_clients.erase(sock);
    }
}

