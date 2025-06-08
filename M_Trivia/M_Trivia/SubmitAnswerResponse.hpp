#pragma once
#include "Response.hpp"
#include "GeneralResponseErrors.hpp"

/**
 * @class CloseRoomResponse
 * @brief Represents a response containing Status only and no data
 */
class SubmitAnswerResponse : public Response {
private:
	unsigned int m_correctAnswerId;
public:
	SubmitAnswerResponse(GeneralResponseErrors* errors, unsigned int correctAnswerId);

	/**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
	ResponseCodes getCode() const override;

	/**
	 * @brief Deleted default constructor to enforce proper initialization.
	 */
	SubmitAnswerResponse() = delete;

	/**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
	nlohmann::json getJson() const override;
};