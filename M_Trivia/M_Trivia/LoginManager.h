#pragma once
#include "IDataBase.h"
#include "LoggedUser.h"
#include "SignupResponseStatus.h"
#include "LoginResponseStatus.h"
#include "SendEmailCodeResponseStatus.h"
#include "ResetPasswordResponseStatus.h"
#include "EmailSender.hpp"
#include <vector>
#include "UserRecord.hpp"
#include "RegexValidator.h"


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
	SignupResponseStatus signup(const UserRecord&) const;
	LoginResponseStatus login(const std::string username, const std::string password);
	SendEmailCodeResponseStatus sendEmailCode(const std::string email, unsigned int code) const;
	ResetPasswordResponseStatus resetPassword(const std::string& username, const std::string& newPassword) const;
	std::string getUsername(const std::string& email) const;
	void logout(const std::string username);
};