#include "GetQuestionResponse.hpp"

GetQuestionResponse::GetQuestionResponse(std::unique_ptr<GeneralResponseErrors> errors, const std::optional<Question>& question) :
	Response(std::move(errors)), m_question(question)
{
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
