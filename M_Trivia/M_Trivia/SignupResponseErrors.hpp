#pragma once
#include <string>
#include "json.hpp"

class SignupResponseErrors {
public:
    // Error fields
    std::string usernameError;
    std::string passwordError;
    std::string emailError;
    std::string phoneNumberError;
    std::string houseAddressError;
    std::string birthDateError;


    unsigned int statusCode;

    /**
     * @brief Checks if all error fields are not set (empty).
     *
     * @return true if all error fields are empty; otherwise, false.
     */
    bool noErrors() const {
        return usernameError.empty() &&
            passwordError.empty() &&
            emailError.empty() &&
            phoneNumberError.empty() &&
            houseAddressError.empty() &&
            birthDateError.empty();
    }

    /**
     * @brief Converts this object into a JSON object.
     *
     * This function serializes the `SignupErrors` object into a JSON object.
     * @param j The JSON object to which the data will be written.
     * @param signupErrors The SignupErrors object that contains the data to be serialized.
     */
    friend void to_json(nlohmann::json& j, const SignupResponseErrors& signupErrors) {
        j = nlohmann::json{
            {"UsernameError", signupErrors.usernameError},
            {"PasswordError", signupErrors.passwordError},
            {"EmailError", signupErrors.emailError},
            {"PhoneNumberError", signupErrors.phoneNumberError},
            {"HouseAddressError", signupErrors.houseAddressError},
            {"BirthDateError", signupErrors.birthDateError}
        };
    }
};
