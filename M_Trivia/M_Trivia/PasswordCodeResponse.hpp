#pragma once
#include "PasswordCodeResponseErrors.hpp"
#include "Response.hpp"
#include <string>

class PasswordCodeResponse : public Response {
private:

public:
  PasswordCodeResponse() = delete;
  PasswordCodeResponse(PasswordCodeResponseErrors *errors);

  /**
   * @brief Gets the response code for this response.
   * @return The response code as an unsigned integer.
   */
  ResponseCodes getCode() const override;

};
