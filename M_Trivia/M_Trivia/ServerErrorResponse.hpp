#pragma once
#include <string>
#include "json.hpp"
#include "Response.hpp"

/**
 * @class ErrorResponse
 * @brief Represents a response containing an error message
 */
struct ServerErrorResponse : public Response<ResponseCodes::C_ErrorResponse> {
private:
    std::string message;

public:
    ServerErrorResponse(const std::string& message);



    nlohmann::json getJson() const override;
};