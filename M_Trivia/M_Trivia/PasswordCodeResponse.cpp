#include "PasswordCodeResponse.hpp"

#include "json.hpp"

PasswordCodeResponse::PasswordCodeResponse(PasswordCodeResponseErrors *errors)
    : Response(errors) {}

ResponseCodes PasswordCodeResponse::getCode() const {
  return ResponseCodes::C_SendPasswordResetCodeResponse;
}
