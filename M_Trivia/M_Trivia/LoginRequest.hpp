#pragma once
#include <string>
#include "json.hpp"

/**
 * @class LoginRequest
 * @brief Represents a request to log in.
 */
class LoginRequest {
    friend void from_json(const nlohmann::json& j, LoginRequest& request);

private:
    std::string username;
    std::string password;

public:
    LoginRequest() = default;

    const std::string& getUsername() const { return username; }
    const std::string& getPassword() const { return password; }

    /**
     * @brief Deserializes a JSON object into a LoginRequest object.
     *
     * @param j The JSON object to deserialize.
     * @param request The LoginRequest object to populate.
     */
    friend void from_json(const nlohmann::json& j, LoginRequest& request) {
        j.at("Username").get_to(request.username);
        j.at("Password").get_to(request.password);
    }
};
