#pragma once
#include <string>
#include "json.hpp"

class IResponseErrors {
public:
    unsigned int statusCode;

    /**
     * @brief Checks if all error fields are not set (empty).
     *
     * @return true if all error fields are empty; otherwise, false.
     */
    virtual bool noErrors() const = 0;

    virtual nlohmann::json getJson() const = 0;
};
