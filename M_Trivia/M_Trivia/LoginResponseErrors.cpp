#include "LoginResponseErrors.hpp"

bool LoginResponseErrors::noErrors() const {
  return passwordError.empty() && usernameError.empty() && generalError.empty();
}

nlohmann::json LoginResponseErrors::getJson() const {
  nlohmann::json j = nlohmann::json{
      {"PasswordError", passwordError},
      {"UsernameError", usernameError},
      {"GeneralError", generalError},
  };
  return j;
}
