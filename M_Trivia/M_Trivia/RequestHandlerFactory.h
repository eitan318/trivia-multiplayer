#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
//#include "IDatabase.h"

class RequestHandlerFactory {
private:
	//IDatabase* m_database
	LoginManager m_loginManager;
public:
	LoginRequestHandler* createLoginRequestHandler();
};