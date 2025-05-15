#include "SendPasswordResetCodeRequest.hpp"

SendPasswordResetCodeRequest::SendPasswordResetCodeRequest(
    const nlohmann::json &j)
    : email(j.at("Email")) {}

const std::string &SendPasswordResetCodeRequest::getEmail() const {
  return email;
}
