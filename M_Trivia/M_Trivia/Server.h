#pragma once
#include "Communicator.h"
#include <thread>
#include <string>
#include <iostream>

class Server
{
private:
	Communicator m_communicator;
public:
	void run();
	Server();
	~Server();

};

