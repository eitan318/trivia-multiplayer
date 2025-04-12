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

SignupResponseStatus LoginManager::signup(const UserRecord& userRecord)
{
    // PASSWORD
    std::regex passwordRegex(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[!@#$%^&*]).{8,}$)");
    if (!std::regex_match(userRecord.password, passwordRegex)) {
        return SignupResponseStatus::InvalidPassword;
    }

    // EMAIL
    std::regex emailRegex(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.(com|co\.il|cyber\.org\.il)$)");
    if (!std::regex_match(userRecord.email, emailRegex)) {
        return SignupResponseStatus::InvalidEmailFormat;
    }

    // ADDRESS (format: Street, Apt, City)
    std::smatch match;
    std::regex addressRegex(R"(^([A-Za-z\s]+),\s*(\d+),\s*([A-Za-z\s]+)$)");
    if (!std::regex_match(userRecord.houseAddress, match, addressRegex)) {
        return SignupResponseStatus::InvalidHousAddress;
    }
    std::string street = match[1];
    std::string apt = match[2];
    std::string city = match[3];

    // PHONE
    std::regex phoneRegex(R"(^0(2|3|4|5\d)-\d{7}$)");
    if (!std::regex_match(userRecord.phoneNumber, phoneRegex)) {
        return SignupResponseStatus::InvalidPhoneNumber;
    }

    // BIRTH DATE
    std::regex dateRegex(R"(^(0[1-9]|[12][0-9]|3[01])[-/.](0[1-9]|1[0-2])[-/.](19|20)\d{2}$)");
    if (!std::regex_match(userRecord.birthDate, dateRegex))
        return SignupResponseStatus::InvalidBirthDate;
  
	if (this->m_database->doesUserExist(userRecord.username)) 
		return SignupResponseStatus::KnowenUsername;

    this->m_database->addNewUser(userRecord);

    return SignupResponseStatus::Success;
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

