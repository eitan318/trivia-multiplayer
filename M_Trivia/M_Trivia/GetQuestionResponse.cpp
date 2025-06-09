#include "GetQuestionResponse.hpp"

GetQuestionResponse::GetQuestionResponse(unsigned int status, const Question& question) :
	Response(status), m_question(question)
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
