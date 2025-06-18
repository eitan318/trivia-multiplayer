#pragma once
#include <string>
#include "json.hpp"
#include "IResponseErrors.hpp"
	
class CloseRoomResponseErrors : public IResponseErrors {
public:
	std::string generalError;

	/**
	 * @brief Checks if all error fields are not set (empty).
	 *
	 * @return true if all error fields are empty; otherwise, false.
	 */
	bool noErrors() const override;

	nlohmann::json getJson() const override;
};