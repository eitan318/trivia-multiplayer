#pragma once
#include <string>
#include "json.hpp"
#include "Response.hpp"

/**
 * @class ErrorResponse
 * @brief Represents a response containing an error message
 */
struct ServerErrorResponse : public Response{
private:
    std::string message;

public:
    ServerErrorResponse() = delete;

    ServerErrorResponse(const std::string& message);

    /**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
    ResponseCodes getCode() const override;



    nlohmann::json getJson() const override;
};