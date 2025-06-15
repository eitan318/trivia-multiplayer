#include "LoginManager.hpp"

#include "EmailSender.hpp"
#include "MyException.hpp"
#include "RegexValidator.hpp"
#include "UserRecord.hpp"
#include <string>

LoginManager::LoginManager(IDatabase& database) : m_database(database) {}
LoginManager& LoginManager::getInstance(IDatabase& database) {
    static LoginManager instance(database);
    return instance;
}

LoginResponseErrors LoginManager::login(const std::string username,
    const std::string password, SOCKET sock) {
    LoginResponseErrors errors;

    if (this->m_loggedUsers.find(username) != m_loggedUsers.end()) {
        errors.generalError = "User already logged in";
    }
    else if (!this->m_database.doesUserExist(username) ||
        !this->m_database.doesPasswordMatch(username, password)) {
        errors.generalError = "Unknown username or wrong password";
    }

    if (errors.statusCode() == 0) {
        m_loggedUsers.emplace(username, LoggedUser(username));
        m_usernames.emplace(sock, username);
    }
    return errors;
}

PasswordCodeResponseErrors LoginManager::sendEmailCode(const std::string email,
    unsigned int code) {
    PasswordCodeResponseErrors errors;
    if (!RegexValidator::validEmail(email)) {
        errors.emailErrors = std::string() + "Invalid email format, Use: " +
            RegexValidator::emailRegexDescription.data();
    }
    else if (!this->m_database.emailExists(email)) {
        return errors;
    }
    this->prevRandomCode = code;

    if (errors.statusCode() == 0) {
        EmailSender::sendEmail("servicehandler055@gmail.com", email,
            "Reset Password Code",
            "Code: " + std::to_string(code));
    }

    return errors;
}

GeneralResponseErrors LoginManager::verifyResetPasswordCode(const std::string& codeFromClient,
    const std::string& resetPasswordTocken) {
    this->prevResetPasswordTocken = resetPasswordTocken;
    GeneralResponseErrors errors;
    if (codeFromClient != std::to_string(this->prevRandomCode)) {
        errors.generalError = "Wrong code";
    }

    return errors;
}

ResetPasswordResponseErrors
LoginManager::resetPassword(const std::string& email,
    const std::string& newPassword,
    const std::string& resetPasswordTocken) {

    ResetPasswordResponseErrors resetPasswordErrors;
    if (!RegexValidator::validUsername(email)) {
        resetPasswordErrors.generalError =
            std::string() + "Invalid username. Use: " +
            RegexValidator::usernameRegexDescription.data();
    }
    else if (resetPasswordTocken != this->prevResetPasswordTocken) {
        resetPasswordErrors.generalError =
            std::string() + "Invalid reset password tocken";
    }

    if (!RegexValidator::validPassword(newPassword)) {
        resetPasswordErrors.newPasswordError =
            std::string() + "Invalid password. Use: " +
            RegexValidator::passwordRegexDescription.data();
    }


    UserRecord userRecord;
    try {
        userRecord = this->m_database.getUserRecord(email);
    }
    catch (MyException e) {
        // email does not exist, do not give fidback to user
        return resetPasswordErrors;
    }

    if (resetPasswordErrors.statusCode() == 0) {
        this->m_database.updatePassword(userRecord.username, newPassword);
        this->prevResetPasswordTocken = resetPasswordTocken;
    }

    return resetPasswordErrors;
}

std::string LoginManager::getUsername(const std::string& email) const {
    return this->m_database.getUserRecord(email).username;
}

SignupResponseErrors LoginManager::signup(const UserRecord& userRecord) const {
    SignupResponseErrors signupErrors;

    if (!RegexValidator::validUsername(userRecord.username)) {
        signupErrors.usernameError =
            std::string() + "Invalid format. Use: " +
            RegexValidator::usernameRegexDescription.data();
    }
    else if (this->m_database.doesUserExist(userRecord.username)) {
        signupErrors.usernameError = "User already exist";
    }

    if (!RegexValidator::validPassword(userRecord.password)) {
        signupErrors.passwordError =
            std::string() + "Password must be " +
            RegexValidator::passwordRegexDescription.data();
    }

    if (!RegexValidator::validEmail(userRecord.email)) {
        signupErrors.emailError = std::string() + "Invalid format. Use: " +
            RegexValidator::emailRegexDescription.data();
    }
    else if (this->m_database.emailExists(userRecord.email)) {
        signupErrors.emailError = "User with this email exist.";
    }

    if (userRecord.houseAddress != "" &&
        !RegexValidator::validHouseAddress(userRecord.houseAddress)) {
        signupErrors.houseAddressError =
            std::string() + "Invalid format. Use: " +
            RegexValidator::houseAddressRegexDescription.data();
    }

    if (userRecord.phoneNumber != "" &&
        !RegexValidator::validPhoneNumber(userRecord.phoneNumber)) {
        signupErrors.phoneNumberError =
            std::string() + "Invalid format. Use: " +
            RegexValidator::phoneNumberRegexDescription.data();
    }

    if (userRecord.birthDate != "" &&
        !RegexValidator::validBirthDate(userRecord.birthDate)) {
        signupErrors.birthDateError =
            std::string() + "Invalid format. Use: " +
            RegexValidator::birthDateRegexDescription.data();
    }


    if (signupErrors.statusCode() == 0) {
        this->m_database.addNewUser(userRecord);
    }

    return signupErrors;
}

void LoginManager::logout(const std::string& user) {
    auto it = m_loggedUsers.find(user);
    if (it != m_loggedUsers.end()) {
        // Remove the associated socket
        auto socketIt = std::find_if(m_usernames.begin(), m_usernames.end(),
            [&user](const auto& pair) { return pair.second == user; });
        if (socketIt != m_usernames.end()) {
            m_usernames.erase(socketIt);
        }
        m_loggedUsers.erase(it);
    }
}

void LoginManager::logout(const SOCKET sock) {
    auto it = m_usernames.find(sock);
    if (it != m_usernames.end()) {
        m_loggedUsers.erase(it->second); // Remove user from logged users
        m_usernames.erase(it);          // Remove socket from usernames map
    }
}

