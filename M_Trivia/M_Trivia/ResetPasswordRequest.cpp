#include "ResetPasswordRequest.hpp"

ResetPasswordRequest::ResetPasswordRequest(const nlohmann::json &j)
    : username(j.at("Username")), newPassword(j.at("NewPassword")) {}

const std::string &ResetPasswordRequest::getUsername() const {
  return username;
}

const std::string &ResetPasswordRequest::getNewPassword() const {
  return newPassword;
}
