#pragma once
#include "json.hpp"
#include "HighScoreInfo.hpp"
#include "Response.hpp"
#include "SignupResponseErrors.hpp"
#include <vector>

/**
 * @class SignupResponse
 * @brief Represents a response containing Status and a regex result.
 */
class SignupResponse : public Response {
private:
    SignupResponseErrors signupResponseErrors; 
public:
    /**
     * @brief Constructor for SignupResponse.
     * @param status The status of the response.
     * @param regexResult A vector of boolean values representing the regex result.
     */
    SignupResponse(const SignupResponseErrors& signupResponseErrors)
        : Response(signupResponseErrors.statusCode), signupResponseErrors(signupResponseErrors) {
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
        j["Errors"] = signupResponseErrors;
        return j;
    }
};
