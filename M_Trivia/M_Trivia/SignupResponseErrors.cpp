#include "SignupResponseErrors.hpp"
#include "json.hpp"

bool SignupResponseErrors::noErrors() const{
	return usernameError.empty() &&
		passwordError.empty() &&
		emailError.empty() &&
		phoneNumberError.empty() &&
		houseAddressError.empty() &&
		birthDateError.empty();
}



nlohmann::json SignupResponseErrors::getJson() const {
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
