#include "GetQuestionResponse.hpp"

GetQuestionResponse::GetQuestionResponse(GeneralResponseErrors* errors, const std::optional<Question>& question) :
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
    if (m_question.has_value()) {
        j["Question"] = m_question.value();
    }
    else {
        j["Question"] = "No question";
    }
    return j;
}
