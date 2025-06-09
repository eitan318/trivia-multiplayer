#include "SubmitAnswerResponse.hpp"

SubmitAnswerResponse::SubmitAnswerResponse(GeneralResponseErrors* errors, unsigned int correctAnswerId)
    : Response(errors), m_correctAnswerId(correctAnswerId)
{
}

ResponseCodes SubmitAnswerResponse::getCode() const
{
    return ResponseCodes::C_SubmitAnswerResponse;
}

nlohmann::json SubmitAnswerResponse::getJson() const
{
	nlohmann::json j = Response::getJson();
	j["CorrectAnswerId"] = m_correctAnswerId;
	return j;
}
