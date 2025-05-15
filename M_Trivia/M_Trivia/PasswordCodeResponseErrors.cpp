#include "PasswordCodeResponseErrors.hpp"

bool PasswordCodeResponseErrors::noErrors() const {
  return emailErrors.empty();
}

nlohmann::json PasswordCodeResponseErrors::getJson() const {
  nlohmann::json j = nlohmann::json{
      {"EmailError", emailErrors},
  };
  return j;
}
