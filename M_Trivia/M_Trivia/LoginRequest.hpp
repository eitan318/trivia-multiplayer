#pragma once
#include <string>
#include "json.hpp"

template <typename T>
class JsonRequestPacketDeserializer;


/**
 * @class LoginRequest
 * @brief Represents a request to log in.
 */
class LoginRequest {
    friend class JsonRequestPacketDeserializer<LoginRequest>;
private:
    std::string username;
    std::string password;

    LoginRequest(const nlohmann::json& j) :
        username(j.at("Username")),
        password(j.at("Password"))
    {
    }

public:
    const std::string& getUsername() const { return username; }
    const std::string& getPassword() const { return password; }
};
