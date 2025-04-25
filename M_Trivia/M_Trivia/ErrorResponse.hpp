#pragma once
#include <string>
#include "json.hpp"
#include "Response.hpp"

/**
 * @class ErrorResponse
 * @brief Represents a response containing an error message
 */
struct ErrorResponse : public Response{
public:

    /**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
    unsigned char getCode() const { return C_ErrorResponse; }

	std::string message;

    nlohmann::json getJson() const override {
        nlohmann::json j = baseJson();
        j["Message"] = message; 
        return j;
    }
};