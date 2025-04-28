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

LoginResponseErrors LoginManager::login(const std::string username, const std::string password)
{
	LoginResponseErrors errors;
	if (!this->m_database->doesUserExist(username))
		errors.usernameError = "Unknown username";
	else if(!this->m_database->doesPasswordMatch(username, password)) {
		errors.passwordError = "Wrong password";
	}
	errors.statusCode = !errors.noErrors();

	if (errors.statusCode == 0) {
		LoggedUser loggeduser;
		loggeduser.m_username = username;
		this->m_loggedUsers.push_back(loggeduser);
	}
	return errors;
}

PasswordCodeResponseErrors LoginManager::sendEmailCode(const std::string email, unsigned int code) const
{
	PasswordCodeResponseErrors errors;
	if (!RegexValidator::validEmail(email))
		errors.emailErrors = std::string() + "Invalid email format, Use: " + RegexValidator::emailRegexDescription.data();
	else if (!this->m_database->emailExists(email)) 
		errors.emailErrors = "Email doesnt exist";

	errors.statusCode = !errors.noErrors();
	if (errors.statusCode == 0) {
		EmailSender::sendEmail("servicehandler055@gmail.com", email,
			"Reset Password Code", "Code: " + std::to_string(code));
	}

	return errors;
}

ResetPasswordResponseErrors LoginManager::resetPassword(const std::string& username, const std::string& newPassword) const
{
	ResetPasswordResponseErrors resetPasswordErrors;
	if (!RegexValidator::validUsername)
		resetPasswordErrors.generalError = std::string() + "Invalid username. Use: " + RegexValidator::usernameRegexDescription.data();

	if (!this->m_database->doesUserExist(username))
		resetPasswordErrors.generalError = std::string() + "Unknown username: " + username;

	if (!RegexValidator::validPassword(newPassword))
		resetPasswordErrors.newPasswordError = std::string() + "Invalid password. Use: " + RegexValidator::passwordRegexDescription.data();

	resetPasswordErrors.statusCode = !resetPasswordErrors.noErrors();

	if (resetPasswordErrors.statusCode == 0) {
		this->m_database->updatePassword(username, newPassword);
	}

	return resetPasswordErrors;
	
}

std::string LoginManager::getUsername(const std::string& email) const
{
	return this->m_database->getUserRecord(email).username;
}

SignupResponseErrors LoginManager::signup(const UserRecord& userRecord) const
{
	SignupResponseErrors signupErrors;

	if (!RegexValidator::validUsername(userRecord.username))
		signupErrors.usernameError = std::string() + "Invalid format. Use: " + RegexValidator::usernameRegexDescription.data();
	else if (this->m_database->doesUserExist(userRecord.username))
		signupErrors.usernameError = "User already exist";

	if (!RegexValidator::validPassword(userRecord.password))
		signupErrors.passwordError = std::string() + "Password must be " + RegexValidator::passwordRegexDescription.data();

	if (!RegexValidator::validEmail(userRecord.email))
		signupErrors.emailError = std::string() + "Invalid format. Use: " + RegexValidator::emailRegexDescription.data();

	if (userRecord.houseAddress != "" && !RegexValidator::validHouseAddress(userRecord.houseAddress))
		signupErrors.houseAddressError = std::string() + "Invalid format. Use: " + RegexValidator::houseAddressRegexDescription.data();

    if (userRecord.phoneNumber != "" && !RegexValidator::validPhoneNumber(userRecord.phoneNumber))
        signupErrors.phoneNumberError = std::string() + "Invalid format. Use: " + RegexValidator::phoneNumberRegexDescription.data();

	if (userRecord.birthDate != "" && !RegexValidator::validBirthDate(userRecord.birthDate))
		signupErrors.birthDateError = std::string() + "Invalid format. Use: " + RegexValidator::birthDateRegexDescription.data();

	signupErrors.statusCode = !signupErrors.noErrors();

	if (signupErrors.statusCode == 0) {
		this->m_database->addNewUser(userRecord);
	}

    return signupErrors;
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

