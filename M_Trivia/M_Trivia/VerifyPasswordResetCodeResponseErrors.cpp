#include "VerifyPasswordResetCodeResponseErrors.hpp"
#include "json.hpp"

bool VerifyPasswordResetCodeResponseErrors::noErrors() const {
	return this->generalError.empty();
}

nlohmann::json VerifyPasswordResetCodeResponseErrors::getJson() const {
	nlohmann::json j = nlohmann::json{ {"GeneralError", this->generalError} };
	return j;
}
