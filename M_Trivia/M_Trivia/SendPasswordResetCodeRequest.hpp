#pragma once
#include "json.hpp"
#include <string>

template <typename T> class JsonRequestPacketDeserializer;

/**
 * @class SendPasswordResetCodeRequest
 * @brief Represents a request to send the password-reset code to an email.
 */
class SendPasswordResetCodeRequest {
  friend class JsonRequestPacketDeserializer<SendPasswordResetCodeRequest>;

private:
  std::string email;
  SendPasswordResetCodeRequest(const nlohmann::json &j);

public:
  const std::string &getEmail() const;
};
