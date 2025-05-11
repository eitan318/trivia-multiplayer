#pragma once
#include <string>
#include "json.hpp"
#include "IResponseErrors.hpp"

class ResetPasswordResponseErrors : public IResponseErrors {
public:
    // Error fields
    std::string generalError;
    std::string newPasswordError;

    /**
     * @brief Checks if all error fields are not set (empty).
     *
     * @return true if all error fields are empty; otherwise, false.
     */
    bool noErrors() const override{
        return newPasswordError.empty()
            && generalError.empty();
    }

    nlohmann::json getJson() const override {
        nlohmann::json j = nlohmann::json{
            {"NewPasswordError", newPasswordError},
            {"GeneralError", generalError},
        };
        return j;
    }
};
