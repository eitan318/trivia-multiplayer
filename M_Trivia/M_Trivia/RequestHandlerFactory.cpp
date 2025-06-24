#include "RequestHandlerFactory.hpp"


#include "LoginRequestHandler.hpp"
#include "MenuRequestHandler.hpp"
#include "RoomAdminRequestHandler.hpp"
#include "Waiting1v1RequestHandler.hpp"
#include "GameRequestHandler.hpp"



RequestHandlerFactory::RequestHandlerFactory(IDatabase& database)
	: m_database(database),
	m_loginManager(LoginManager::getInstance(database)),
	m_statisticsManager(StatisticsManager::getInstance(database)),
	m_roomManager(RoomManager::getInstance(database)),
	m_gameManager(GameManager::getInstance(database)),
	m_waiting1v1Manager(Waiting1v1Manager::getInstance(m_gameManager))
{}



RequestHandlerFactory& RequestHandlerFactory::getInstance(IDatabase& database)
{
	static RequestHandlerFactory instance(database);
	return instance;
}

std::shared_ptr<IRequestHandler> RequestHandlerFactory::createLoginRequestHandler() const 
{
	return std::make_shared<LoginRequestHandler>(const_cast<RequestHandlerFactory&>(*this));
}

std::shared_ptr<IRequestHandler> RequestHandlerFactory::createMenuRequestHandler(const LoggedUser& loggedUser) const
{
	return std::make_shared<MenuRequestHandler>(loggedUser, const_cast<RequestHandlerFactory&>(*this));
}

std::shared_ptr<IRequestHandler> RequestHandlerFactory::createRoomAdminRequestHandler(const LoggedUser& loggedUser, std::shared_ptr<Room> room) const
{
	return std::make_shared<RoomAdminRequestHandler>(const_cast<RequestHandlerFactory&>(*this), loggedUser, room);
}

std::shared_ptr<IRequestHandler> RequestHandlerFactory::createRoomRequestHandler(const LoggedUser& loggedUser, std::shared_ptr<Room> room) const
{
	return std::make_shared<RoomRequestHandler>(const_cast<RequestHandlerFactory&>(*this), loggedUser, room);
}

std::shared_ptr<IRequestHandler> RequestHandlerFactory::createWaiting1v1RequestHandler(const LoggedUser& loggedUser) const
{
	return std::make_shared<Waiting1v1RequestHandler>(const_cast<RequestHandlerFactory&>(*this), loggedUser);
}

std::shared_ptr<IRequestHandler> RequestHandlerFactory::createGameRequestHandler(LoggedUser user, std::shared_ptr<Game> game,
	std::shared_ptr<RoomPreview> roomPreview, std::shared_ptr<IRequestHandler> prevRequestHandler)
{
	return std::make_shared<GameRequestHandler>(user,const_cast<RequestHandlerFactory&>(*this), game, roomPreview, prevRequestHandler);
}

LoginManager& RequestHandlerFactory::getLoginManager() const
{
	return this->m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManger() const
{
	return this->m_roomManager;
}

GameManager& RequestHandlerFactory::getGameManager() const
{
	return this->m_gameManager;
}

Waiting1v1Manager& RequestHandlerFactory::getWaiting1v1Manager() const
{
	return this->m_waiting1v1Manager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManger() const
{
	return this->m_statisticsManager;
}

AddAnswerManager& RequestHandlerFactory::getAddAnswerManager() const
{
	return this->m_addAnswerManager;
}
