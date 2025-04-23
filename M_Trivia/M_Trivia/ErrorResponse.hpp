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
    unsigned int getCode() const { return C_ErrorResponse; }

	std::string message;

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */ 
    nlohmann::json getJson() const{
        return nlohmann::json {
            {"Message", message},
        };
    }
};