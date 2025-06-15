#pragma once
#include "Response.hpp"
#include "GeneralResponseErrors.hpp"

/**
 * @class CloseRoomResponse
 * @brief Represents a response containing Status only and no data
 */
class SubmitAnswerResponse : public Response<ResponseCodes::C_SubmitAnswerResponse, GeneralResponseErrors> {
private:
	unsigned int m_correctAnswerId;
	int m_answerScore;
public:
	SubmitAnswerResponse(std::unique_ptr<GeneralResponseErrors> errors, unsigned int correctAnswerId,
	 int answerScore);

	/**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
	nlohmann::json getJson() const override;
};