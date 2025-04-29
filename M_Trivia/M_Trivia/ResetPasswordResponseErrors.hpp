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

    /**
     * @brief Converts this object into a JSON object.
     *
     * This function serializes the `SignupErrors` object into a JSON object.
     * @param j The JSON object to which the data will be written.
     * @param signupErrors The SignupErrors object that contains the data to be serialized.
     */
    friend void to_json(nlohmann::json& j, const ResetPasswordResponseErrors& signupErrors) {
        
    }
    nlohmann::json getJson() const override {
        nlohmann::json j = nlohmann::json{
            {"NewPasswordError", newPasswordError},
            {"GeneralError", generalError},
        };
        return j;
    }
};
