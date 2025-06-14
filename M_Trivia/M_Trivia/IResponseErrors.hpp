#pragma once
#include "json.hpp"

class IResponseErrors {
public:
    /**
	 * @brief Retrieves the status code.
	 *
	 * @return 0 if there are no errors; otherwise, a non-zero value indicating the presence of errors.
	 */
    unsigned int statusCode() const {
        return noErrors() ? 0 : 1;
    }

    /**
     * @brief Checks if all error fields are not set (empty).
     *
     * @return true if all error fields are empty; otherwise, false.
     */
    virtual bool noErrors() const = 0;

    virtual nlohmann::json getJson() const = 0;

    virtual ~IResponseErrors() {}
};
