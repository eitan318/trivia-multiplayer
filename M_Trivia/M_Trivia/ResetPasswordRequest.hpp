#pragma once
#include "json.hpp"
#include <string>

template <typename T> class JsonRequestPacketDeserializer;

/**
 * @class ResetPasswordRequest
 * @brief Represents a request to reset a user's password.
 */
class ResetPasswordRequest {
  friend class JsonRequestPacketDeserializer<ResetPasswordRequest>;

private:
  std::string username;
  std::string newPassword;

  ResetPasswordRequest(const nlohmann::json &j);

public:
  const std::string &getUsername() const;
  const std::string &getNewPassword() const;
};
