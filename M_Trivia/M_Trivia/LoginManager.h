#pragma once
#include "IDataBase.h"
#include "LoggedUser.h"
#include "SignupResponseStatus.h"
#include "LoginResponseStatus.h"
#include <vector>
#include "UserRecord.hpp"
#include <regex>



class LoginManager {
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
	LoginManager(IDatabase& database);
	~LoginManager() = default;
	LoginManager (const LoginManager&) = delete;
	LoginManager& operator=(const LoginManager&) = delete;
public:
	static LoginManager& getInstance(IDatabase& database);
	SignupResponseStatus signup(const UserRecord&);
	LoginResponseStatus login(const std::string username, const std::string password);
	void logout(const std::string username);
};