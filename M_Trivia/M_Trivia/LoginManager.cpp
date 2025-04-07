#include "LoginManager.h"

LoginManager::LoginManager(IDatabase& database)
{
	this->m_database = &database;
}
LoginManager& LoginManager::getInstance(IDatabase& database)
{
	static LoginManager instance(database);
	return instance;
}
int LoginManager::signup(const UserRecord& userRecord)
{
	if (this->m_database->doesUserExist(userRecord.username)) 
	{
		return false;
	}
	return this->m_database->addNewUser(userRecord);
}
int LoginManager::login(const std::string username, const std::string password)
{
	if (!this->m_database->doesUserExist(username)) 
	{
		return false;
	}
	if (this->m_database->doesPasswordMatch(username, password)) 
	{
		LoggedUser loggeduser;
		loggeduser.m_username = username;
		this->m_loggedUsers.push_back(loggeduser);
		return true;
	}
	return false;
	
}
void LoginManager::logout(const std::string username)
{
	for (auto loggedUser = this->m_loggedUsers.begin(); loggedUser != this->m_loggedUsers.end(); ++loggedUser) //goes through the vector
	{
		if (loggedUser->m_username == username) //if 
		{
			this->m_loggedUsers.erase(loggedUser);
			return; //stops after removing
		}
	}
}

