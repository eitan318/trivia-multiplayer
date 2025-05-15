#pragma once
#include "UserRecord.hpp"
#include "json.hpp"

template <typename T> class JsonRequestPacketDeserializer;

/**
 * @class SignupRequest
 * @brief Represents a request to signup a user.
 */
class SignupRequest {
  friend class JsonRequestPacketDeserializer<SignupRequest>;

private:
  UserRecord userRecord;

  SignupRequest(const nlohmann::json &j);

public:
  const UserRecord &getUserRecord() const;
};
