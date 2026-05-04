#include "ResetPasswordResponseErrors.hpp"

bool ResetPasswordResponseErrors::noErrors() const {
  return newPasswordError.empty() && generalError.empty();
}
nlohmann::json ResetPasswordResponseErrors::getJson() const {
  nlohmann::json j = nlohmann::json{
      {"NewPasswordError", newPasswordError},
      {"GeneralError", generalError},
  };
  return j;
}
