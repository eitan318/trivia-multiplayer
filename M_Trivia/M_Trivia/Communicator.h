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


class Communicator {
private:
	std::map<SOCKET, IRequestHandler*> m_clients;
	SOCKET m_serverSocket;
	RequestHandlerFactory& m_handlerFactory;

public:
	Communicator(RequestHandlerFactory& handlerFactory);
	~Communicator();
	void startHandleRequest();
	void bindAndListen();
	void handleNewClient(SOCKET);

};
