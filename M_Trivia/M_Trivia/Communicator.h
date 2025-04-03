#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include <iostream>
#include <thread>


class Communicator {
private:
	std::map<SOCKET, IRequestHandler*> m_clients;
	SOCKET m_serverSocket;

public:
	Communicator();
	~Communicator();
	void startHandleRequest();
	void bindAndListen();
	void handleNewClient(SOCKET);

};
