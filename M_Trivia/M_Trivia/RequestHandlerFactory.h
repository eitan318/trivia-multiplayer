#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "RoomManager.h"
#include "StatisticsManager.h"


class LoginRequestHandler;


class RequestHandlerFactory {
public:
	static RequestHandlerFactory& getInstance(IDatabase& database);
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager() const;
	RoomManager& getRoomManger() const;
	StatisticsManager& getStatusticsManger() const;
private:
	RoomManager& m_roomManager;
	IDatabase* m_database;
	StatisticsManager& m_statisticsManager;
	LoginManager& m_loginManager;
	RequestHandlerFactory(IDatabase& database);
	RequestHandlerFactory(const RequestHandlerFactory&) = delete;
	RequestHandlerFactory& operator=(const RequestHandlerFactory&) = delete;
};