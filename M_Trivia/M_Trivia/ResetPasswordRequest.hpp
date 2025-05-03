#pragma once
#include <string>
#include "json.hpp"

/**
 * @class ResetPasswordRequest
 * @brief Represents a request to reset a user's password.
 */
class ResetPasswordRequest {
    friend void from_json(const nlohmann::json& j, ResetPasswordRequest& request);

private:
    std::string username;
    std::string newPassword;

public:
    ResetPasswordRequest() = default;

    const std::string& getUsername() const { return username; }
    const std::string& getNewPassword() const { return newPassword; }

    /**
     * @brief Deserializes a JSON object into a ResetPasswordRequest object.
     *
     * @param j The JSON object to deserialize.
     * @param request The ResetPasswordRequest object to populate.
     */
    friend void from_json(const nlohmann::json& j, ResetPasswordRequest& request) {
        j.at("Username").get_to(request.username);
        j.at("NewPassword").get_to(request.newPassword);
    }
};
