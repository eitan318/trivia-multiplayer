#pragma once
#include <string>
#include "json.hpp"
#include "IResponseErrors.hpp"

class JoinRoomResponseErrors : public IResponseErrors {
public:
    // Error fields
    std::string generalError;

    /**
     * @brief Checks if all error fields are not set (empty).
     *
     * @return true if all error fields are empty; otherwise, false.
     */
    bool noErrors() const override {
        return generalError.empty();
    }

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const override {
        nlohmann::json j;
        j["GeneralError"] = generalError;
        return j;
    }
};
