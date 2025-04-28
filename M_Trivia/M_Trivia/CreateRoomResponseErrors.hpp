#pragma once
#include <string>
#include "json.hpp"
#include "IResponseErrors.hpp"

class CreateRoomResponseErrors : public IResponseErrors {
public:
    // Error fields
    std::string questionCountError;

    /**
     * @brief Checks if all error fields are not set (empty).
     *
     * @return true if all error fields are empty; otherwise, false.
     */
    bool noErrors() const override {
        return questionCountError.empty();
    }

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const override {
        nlohmann::json j;
        j["QuestionCountError"] = questionCountError;
        return j;
    }
};
