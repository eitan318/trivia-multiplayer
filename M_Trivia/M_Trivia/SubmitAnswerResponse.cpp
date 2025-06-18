#include "SubmitAnswerResponse.hpp"

SubmitAnswerResponse::SubmitAnswerResponse(std::unique_ptr<GeneralResponseErrors> errors,
	unsigned int correctAnswerId)
    : Response(std::move(errors)), m_correctAnswerId(correctAnswerId){
}


nlohmann::json SubmitAnswerResponse::getJson() const
{
	nlohmann::json j = Response::getJson();
	j["CorrectAnswerId"] = m_correctAnswerId;
	return j;
}
