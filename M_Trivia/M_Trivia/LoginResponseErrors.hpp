#pragma once
#include <string>
#include "json.hpp"

class LoginResponseErrors {
public:
    // Error fields
    std::string usernameError;
    std::string passwordError;

    unsigned int statusCode;

    /**
     * @brief Checks if all error fields are not set (empty).
     *
     * @return true if all error fields are empty; otherwise, false.
     */
    bool noErrors() const {
        return passwordError.empty()
            && usernameError.empty();
    }

    /**
     * @brief Converts this object into a JSON object.
     *
     * This function serializes the `SignupErrors` object into a JSON object.
     * @param j The JSON object to which the data will be written.
     * @param signupErrors The SignupErrors object that contains the data to be serialized.
     */
    friend void to_json(nlohmann::json& j, const LoginResponseErrors& signupErrors) {
        j = nlohmann::json{
            {"PasswordError", signupErrors.passwordError},
            {"UsernameError", signupErrors.usernameError},
        };
    }
};
