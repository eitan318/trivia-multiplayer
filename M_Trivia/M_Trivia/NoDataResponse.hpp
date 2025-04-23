#pragma once
#include "json.hpp"
#include "Response.hpp"

class NoDataResponse : public Response {
public:
    unsigned int status;

    /**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
    unsigned int getCode() const { return C_NoDataResponse; }

    /**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
    nlohmann::json getJson() const {
        return nlohmann::json{
            {"Status", status},
        };
    }
};