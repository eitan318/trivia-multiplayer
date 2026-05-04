#pragma once
#include "IResponseErrors.hpp"
#include "json.hpp"
#include <string>

class LoginResponseErrors : public IResponseErrors {
public:
  // Error fields
  std::string usernameError;
  std::string passwordError;
  std::string generalError;

  /**
   * @brief Checks if all error fields are not set (empty).
   *
   * @return true if all error fields are empty; otherwise, false.
   */
  bool noErrors() const override;

  nlohmann::json getJson() const override;
};
