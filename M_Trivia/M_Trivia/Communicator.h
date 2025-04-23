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


#define PORT 5554


class Communicator {
private:
	std::map<SOCKET, IRequestHandler*> m_clients;
	SOCKET m_serverSocket;
	RequestHandlerFactory& m_handlerFactory;
	Communicator(RequestHandlerFactory& handlerFactory);
	~Communicator();
	Communicator(const Communicator&) = delete;
	Communicator& operator=(const Communicator&) = delete;

public:
	static Communicator& getInstance(RequestHandlerFactory& handlerFactory);
	void startHandleRequest();
	void bindAndListen() const;
	void handleNewClient(SOCKET);

};
