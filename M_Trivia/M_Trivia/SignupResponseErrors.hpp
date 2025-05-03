#pragma once
#include <string>
#include "json.hpp"
#include "IResponseErrors.hpp"

class SignupResponseErrors : public IResponseErrors {
public:
    // Error fields
    std::string usernameError;
    std::string passwordError;
    std::string emailError;
    std::string phoneNumberError;
    std::string houseAddressError;
    std::string birthDateError;


    /**
     * @brief Checks if all error fields are not set (empty).
     *
     * @return true if all error fields are empty; otherwise, false.
     */
    bool noErrors() const override{
        return usernameError.empty() &&
            passwordError.empty() &&
            emailError.empty() &&
            phoneNumberError.empty() &&
            houseAddressError.empty() &&
            birthDateError.empty();
    }

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const override {
        nlohmann::json j = nlohmann::json{
            {"UsernameError", usernameError},
            {"PasswordError", passwordError},
            {"EmailError", emailError},
            {"PhoneNumberError", phoneNumberError},
            {"HouseAddressError", houseAddressError},
            {"BirthDateError", birthDateError}
        };
        return j;
    }
};
