#pragma once
#include "IDatabase.hpp"
#include "LoggedUser.hpp"
#include "LoginResponseErrors.hpp"
#include "PasswordCodeResponseErrors.hpp"
#include "ResetPasswordResponseErrors.hpp"
#include "SignupResponseErrors.hpp"
#include "VerifyPasswordResetCodeResponseErrors.hpp"
#include <unordered_map>

/**
 * @brief Manages user authentication, registration, and session handling.
 */
class LoginManager {
private:
  IDatabase &m_database; ///< Pointer to the database interface for user data.
  unsigned int prevRandomCode;
  std::string prevResetPasswordTocken;
  std::unordered_map<std::string, LoggedUser> m_loggedUsers; ///< List of currently logged-in users.

  /**
     @brief Constructs a LoginManager instance.
   * @param database Reference to the database interface.
   */
  LoginManager(IDatabase &database);

  /**
   * @brief Default destructor.
   */
  ~LoginManager() = default;

  // Disable copy constructor and assignment operator to enforce singleton
  // pattern.
  LoginManager(const LoginManager &) = delete;
  LoginManager &operator=(const LoginManager &) = delete;

public:
  /**
   * @brief Retrieves the singleton instance of LoginManager.
   * @param database Reference to the database interface.
   * @return A reference to the LoginManager instance.
   */
  static LoginManager &getInstance(IDatabase &database);

  /**
   * @brief Registers a new user in the system.
   * @param userRecord Information about the new user.
   * @return Status indicating the result of the signup operation.
   */
  SignupResponseErrors signup(const UserRecord &userRecord) const;

  /**
   * @brief Authenticates a user by their username and password.
   * @param username The user's username.
   * @param password The user's password.
   * @return Status indicating the result of the login operation.
   */
  LoginResponseErrors login(const std::string username,
                            const std::string password);

  /**
   * @brief Sends a password reset code to the user's email.
   * @param email The user's email address.
   * @param code The reset code to be sent.
   * @return Status indicating the result of the email operation.
   */
  PasswordCodeResponseErrors sendEmailCode(const std::string email,
                                           unsigned int code);

  /**
   * @brief Resets a user's password.
   * @param username The user's username.
   * @param newPassword The new password to set.
   * @return Status indicating the result of the reset operation.
   */
  ResetPasswordResponseErrors
  resetPassword(const std::string &username, const std::string &newPassword,
                const std::string &resetPasswordTocken);

  VerifyPasswordResetCodeResponseErrors
  verifyResetPasswordCode(const std::string &codeFromClient, const std::string& resetPasswordTocken);

  /**
   * @brief Retrieves the username associated with a given email.
   * @param email The user's email address.
   * @return The username associated with the email.
   */
  std::string getUsername(const std::string &email) const;

  /**
   * @brief Logs out a user, removing them from the list of active sessions.
   * @param username The username of the user to log out.
   */
  void logout(const std::string &user);
};
