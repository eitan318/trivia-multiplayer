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

    LoginRequest(const nlohmann::json& j) ;

public:
    const std::string& getUsername() const;
    const std::string& getPassword() const;
};
