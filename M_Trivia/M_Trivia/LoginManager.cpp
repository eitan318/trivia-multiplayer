#include "LoginManager.hpp"

#include "EmailSender.hpp"
#include "LoginRequest.hpp"
#include "RegexValidator.hpp"
#include "UserRecord.hpp"
#include "VerifyPasswordResetCodeResponseErrors.hpp"
#include <string>
#include "MyException.hpp"

LoginManager::LoginManager(IDatabase& database) : m_database(database) {}
LoginManager& LoginManager::getInstance(IDatabase& database) {
    static LoginManager instance(database);
    return instance;
}

LoginResponseErrors LoginManager::login(const std::string username,
    const std::string password) {
    LoginResponseErrors errors;

    if (this->m_loggedUsers.find(username) != m_loggedUsers.end()) {
        errors.generalError = "User already logged in";
    }
    else if (!this->m_database.doesUserExist(username) ||
        !this->m_database.doesPasswordMatch(username, password)) {
        errors.generalError = "Unknown username or wrong password";
    }
    errors.statusCode = !errors.noErrors();

    if (errors.statusCode == 0) {
        m_loggedUsers.emplace(username, LoggedUser(username));
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
        errors.statusCode = 0;
        return errors;
    }
    this->prevRandomCode = code;

    errors.statusCode = !errors.noErrors();
    if (errors.statusCode == 0) {
        EmailSender::sendEmail("servicehandler055@gmail.com", email,
            "Reset Password Code",
            "Code: " + std::to_string(code));
    }

    return errors;
}

VerifyPasswordResetCodeResponseErrors
LoginManager::verifyResetPasswordCode(const std::string& codeFromClient, const std::string& resetPasswordTocken) {
    this->prevResetPasswordTocken = resetPasswordTocken;
    VerifyPasswordResetCodeResponseErrors errors;
    if (codeFromClient != std::to_string(this->prevRandomCode)) {
        errors.generalError = "Wrong code";
    }

    errors.statusCode = !errors.noErrors();

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

    resetPasswordErrors.statusCode = !resetPasswordErrors.noErrors();

    UserRecord userRecord;
    try {
        userRecord = this->m_database.getUserRecord(email);
    }
    catch (MyException e) {
        // email does not exist, do not give fidback to user
        return resetPasswordErrors;
    }

    if (resetPasswordErrors.statusCode == 0) {
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

    signupErrors.statusCode = !signupErrors.noErrors();

    if (signupErrors.statusCode == 0) {
        this->m_database.addNewUser(userRecord);
    }

    return signupErrors;
}

void LoginManager::logout(const std::string& user) {
    this->m_loggedUsers.erase(user);
}
