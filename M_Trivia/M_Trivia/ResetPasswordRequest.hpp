#pragma once
#include <string>
#include "json.hpp"

template <typename T>
class JsonRequestPacketDeserializer;


/**
 * @class ResetPasswordRequest
 * @brief Represents a request to reset a user's password.
 */
class ResetPasswordRequest {
    friend class JsonRequestPacketDeserializer<ResetPasswordRequest>;
private:
    std::string username;
    std::string newPassword;

    ResetPasswordRequest(const nlohmann::json& j) :
        username(j.at("Username")),
        newPassword(j.at("NewPassword"))
    {

    }

public:

    const std::string& getUsername() const { return username; }
    const std::string& getNewPassword() const { return newPassword; }

};
