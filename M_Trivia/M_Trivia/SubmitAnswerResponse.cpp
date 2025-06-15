#include "SubmitAnswerResponse.hpp"

SubmitAnswerResponse::SubmitAnswerResponse(std::unique_ptr<GeneralResponseErrors> errors,
	unsigned int correctAnswerId, int answerScore)
    : Response(std::move(errors)), m_correctAnswerId(correctAnswerId), m_answerScore(answerScore)
{
}


nlohmann::json SubmitAnswerResponse::getJson() const
{
	nlohmann::json j = Response::getJson();
	j["CorrectAnswerId"] = m_correctAnswerId;
	j["AnswerScore"] = this->m_answerScore;
	return j;
}
