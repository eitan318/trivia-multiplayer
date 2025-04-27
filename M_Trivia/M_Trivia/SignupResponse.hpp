#pragma once
#include "json.hpp"
#include "HighScoreInfo.hpp"
#include "Response.hpp"
#include <vector>

/**
 * @class SignupResponse
 * @brief Represents a response containing Status and a regex result.
 */
class SignupResponse : public Response {
private:
    std::vector<bool> regexResult; 
public:
    /**
     * @brief Constructor for SignupResponse.
     * @param status The status of the response.
     * @param regexResult A vector of boolean values representing the regex result.
     */
    SignupResponse(unsigned int status, const std::vector<bool>& regexResult)
        : Response(status), regexResult(regexResult) {
    }

    /**
     * @brief Gets the response code for this response.
     * @return The response code as an unsigned char.
     */
    unsigned char getCode() const override { return C_SignupResponse; }

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const override {
        nlohmann::json j = baseJson();
        j["RegexResult"] = regexResult;
        return j;
    }
};
