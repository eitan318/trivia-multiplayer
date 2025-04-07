#pragma once
#include "Communicator.h"
#include <thread>
#include <string>
#include <iostream>
#include "IDatabase.h"
#include "RequestHandlerFactory.h"
#include "SqliteDatabase.h"

class Server
{
private:
	Communicator& m_communicator;
	IDatabase* m_database;
	RequestHandlerFactory& m_handlerFactory;
	Server();
	~Server();
	Server(const Server&) = delete;
	Server& operator=(const Server&) = delete;
public:
	static Server& getInstance();
	void run();
};

