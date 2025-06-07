#pragma once
#include "IResponseErrors.hpp"
#include "json.hpp"
#include <string>

class VerifyPasswordResetCodeResponseErrors : public IResponseErrors {
public:
	// Error fields
	std::string generalError;

	/**
	 * @brief Checks if all error fields are not set (empty).
	 *
	 * @return true if all error fields are empty; otherwise, false.
	 */
	bool noErrors() const override;

	nlohmann::json getJson() const override;
};
