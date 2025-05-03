#pragma once
#include <string>
#include "json.hpp"
#include "IResponseErrors.hpp"

class LoginResponseErrors : public IResponseErrors {
public:
    // Error fields
    std::string usernameError;
    std::string passwordError;

    /**
     * @brief Checks if all error fields are not set (empty).
     *
     * @return true if all error fields are empty; otherwise, false.
     */
    bool noErrors() const override {
        return passwordError.empty()
            && usernameError.empty();
    }

    nlohmann::json getJson() const override {
        nlohmann::json j = nlohmann::json{
            {"PasswordError", passwordError},
            {"UsernameError", usernameError},
        };
        return j;
    }
};
