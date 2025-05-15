#pragma once
#include "IResponseErrors.hpp"
#include "json.hpp"
#include <string>

class CreateRoomResponseErrors : public IResponseErrors {
public:
  // Error fields
  std::string questionCountError;

  /**
   * @brief Checks if all error fields are not set (empty).
   *
   * @return true if all error fields are empty; otherwise, false.
   */
  bool noErrors() const override;

  /**
   * @brief Converts the response to a JSON object.
   * @return A JSON representation of the response.
   */
  nlohmann::json getJson() const override;
};
