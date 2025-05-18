#include "ResetPasswordRequest.hpp"

ResetPasswordRequest::ResetPasswordRequest(const nlohmann::json &j)
    : email(j.at("Email")), newPassword(j.at("NewPassword")),
      resetPasswordTocken(j.at("ResetPasswordTocken")) {}

const std::string &ResetPasswordRequest::getEmail() const {
  return email;
}

const std::string &ResetPasswordRequest::getNewPassword() const {
  return newPassword;
}

const std::string &ResetPasswordRequest::getResetPasswordTocken() const {
  return this->resetPasswordTocken;
}
