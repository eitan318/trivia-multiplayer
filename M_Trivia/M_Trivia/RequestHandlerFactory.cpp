#include "RequestHandlerFactory.h"


RequestHandlerFactory::RequestHandlerFactory(IDatabase& database)
	: m_database(&database),
	m_loginManager(LoginManager::getInstance(database)),
	m_roomManager(RoomManager::getInstance())
{}



RequestHandlerFactory& RequestHandlerFactory::getInstance(IDatabase& database)
{
	static RequestHandlerFactory instance(database);
	return instance;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

LoginManager& RequestHandlerFactory::getLoginManager() const
{
	return this->m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManger() const
{
	return this->m_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatusticsManger() const
{
	return this->m_statisticsManager;
}
