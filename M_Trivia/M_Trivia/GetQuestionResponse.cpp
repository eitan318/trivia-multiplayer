#include "GetQuestionResponse.hpp"

GetQuestionResponse::GetQuestionResponse(std::unique_ptr<GeneralResponseErrors> errors, const std::optional<Question>& question, unsigned int questionNumber) :
	Response(std::move(errors)), m_question(question), m_questionNumber(questionNumber)
{
}

nlohmann::json GetQuestionResponse::getJson() const
{
    nlohmann::json j = Response::getJson();

    if (m_question.has_value()) {
        j["Question"] = m_question.value();
        j["QuestionNumber"] = m_questionNumber;
    }
    else {
        j["Question"] = "No question";
        j["QuestionNumber"] = 0;
    }
    return j;
}
