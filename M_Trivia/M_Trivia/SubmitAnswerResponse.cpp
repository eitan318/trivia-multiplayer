#include "SubmitAnswerResponse.hpp"

SubmitAnswerResponse::SubmitAnswerResponse(GeneralResponseErrors* errors, 
	unsigned int correctAnswerId, int answerScore)
    : Response(errors), m_correctAnswerId(correctAnswerId), m_answerScore(answerScore)
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
	j["AnswerScore"] = this->m_answerScore;
	return j;
}
