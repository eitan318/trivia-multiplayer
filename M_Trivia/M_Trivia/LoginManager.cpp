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

LoginResponseStatus LoginManager::login(const std::string username, const std::string password)
{
	if (!this->m_database->doesUserExist(username))
		return LoginResponseStatus::UnknowenUsername;
	if (!this->m_database->doesPasswordMatch(username, password))
		return LoginResponseStatus::PasswordDoesntMatch;
	LoggedUser loggeduser;
	loggeduser.m_username = username;
	this->m_loggedUsers.push_back(loggeduser);
	return LoginResponseStatus::Success;
}

SendEmailCodeResponseStatus LoginManager::sendEmailCode(const std::string email, unsigned int code)
{
	if (!RegexValidator::validEmail(email))
		return SendEmailCodeResponseStatus::InvalidEmail;

	if (!this->m_database->emailExists(email)) 
		return SendEmailCodeResponseStatus::UnknowenEmail;

	EmailSender::sendEmail("eitanforschool08@gmail.com", email,
		"Reset Password Code", "Code: " + std::to_string(code));

	return SendEmailCodeResponseStatus::Success;
}

ResetPasswordResponseStatus LoginManager::resetPassword(const std::string& username, const std::string& newPassword)
{
	if (!RegexValidator::validUsername)
		return ResetPasswordResponseStatus::InvalidUsername;

	if (!this->m_database->doesUserExist(username))
		return ResetPasswordResponseStatus::UnknowenUsername;

	if (!RegexValidator::validPassword(newPassword))
		return ResetPasswordResponseStatus::InvalidPassword;

	this->m_database->updatePassword(username, newPassword);

	return ResetPasswordResponseStatus::Success;
	
}

std::string LoginManager::getUsername(const std::string& email)
{
	return this->m_database->getUserRecord(email).username;
}

SignupResponseStatus LoginManager::signup(const UserRecord& userRecord)
{
	if (!RegexValidator::validPassword(userRecord.password))
		return SignupResponseStatus::InvalidPassword;

    if (!RegexValidator::validEmail(userRecord.email))
        return SignupResponseStatus::InvalidEmailFormat;

    if (!RegexValidator::validHouseAddress(userRecord.houseAddress))
        return SignupResponseStatus::InvalidHousAddress;

    if (!RegexValidator::validPhoneNumber(userRecord.phoneNumber))
        return SignupResponseStatus::InvalidPhoneNumber;

    if (!RegexValidator::validBirthDate(userRecord.birthDate))
        return SignupResponseStatus::InvalidBirthDate;
  
	if (this->m_database->doesUserExist(userRecord.username)) 
		return SignupResponseStatus::KnowenUsername;

    this->m_database->addNewUser(userRecord);
    return SignupResponseStatus::Success;
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

