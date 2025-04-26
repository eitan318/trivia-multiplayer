#pragma once
#include <string>
#include "json.hpp"
#include "Response.hpp"

/**
 * @class ErrorResponse
 * @brief Represents a response containing an error message
 */
struct ErrorResponse : public Response{
private:
    std::string message;

public:
    ErrorResponse() = delete;

    ErrorResponse(const std::string& message) : Response(0), message(message) {

    }

    /**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
    unsigned char getCode() const { return C_ErrorResponse; }



    nlohmann::json getJson() const override {
        nlohmann::json j = baseJson();
        j["Message"] = message; 
        return j;
    }
};