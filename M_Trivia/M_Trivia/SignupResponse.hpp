#pragma once
#include "json.hpp"
#include "Response.hpp"
#include "SignupResponseErrors.hpp"

/**
 * @class SignupResponse
 * @brief Represents a response containing Status and a regex result.
 */
class SignupResponse : public Response {
public:
    /**
     * @brief Constructor for SignupResponse.
     * @param status The status of the response.
     * @param regexResult A vector of boolean values representing the regex result.
     */
    SignupResponse(std::shared_ptr<SignupResponseErrors> signupResponseErrors)
        : Response(std::move(signupResponseErrors)){
    }


    /**
     * @brief Gets the response code for this response.
     * @return The response code as an unsigned char.
     */
    ResponseCodes getCode() const override { return ResponseCodes::C_SignupResponse; }

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const override {
        nlohmann::json j = baseJson();
        return j;
    }
};
