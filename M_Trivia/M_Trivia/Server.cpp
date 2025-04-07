#include "Server.h"

Server::Server()
	: m_database(SqliteDatabase::getInstance()),
	m_handlerFactory(RequestHandlerFactory::getInstance(*m_database)),
	m_communicator(Communicator::getInstance(m_handlerFactory))
{}

Server::~Server()
{
	delete this->m_database;
}

Server& Server::getInstance()
{
	static Server instance;
	return instance;
}

void Server::run()
{
	//this->m_database = new SqliteDatabase();
	this->m_database->open();
	this->m_communicator.bindAndListen();
	std::thread t_connector = std::thread(&Communicator::startHandleRequest, &this->m_communicator);
	t_connector.detach();

	std::cout << "Write to server:" << std::endl;
	std::string input;
	do {
		std::cout << ">>> ";
		std::getline(std::cin, input);
	} while (input != "EXIT");

}
