#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"


class LoginRequestHandler;


class RequestHandlerFactory {
private:
	IDatabase* m_database;
	LoginManager m_loginManager;	
public:
	RequestHandlerFactory(IDatabase& database);
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
};