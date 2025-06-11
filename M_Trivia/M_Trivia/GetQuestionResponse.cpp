#include "GetQuestionResponse.hpp"

GetQuestionResponse::GetQuestionResponse(GeneralResponseErrors* errors, const Question& question) :
	Response(errors), m_question(question)
{
}

ResponseCodes GetQuestionResponse::getCode() const
{
	return ResponseCodes::C_GetQuestionResponse;
}

nlohmann::json GetQuestionResponse::getJson() const
{
    nlohmann::json j = Response::getJson();
    j["Question"] = m_question;
    return j;
}
