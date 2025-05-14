#pragma once
#include <string>
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
    bool noErrors() const override;

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const override;
};
