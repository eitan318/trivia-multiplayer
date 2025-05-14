#include "Question.hpp"

Question::Question(const std::string & difficulty, int categoryId, const std::string & question,
    const std::string& correctAnswer, const std::string& ans1, const std::string& ans2,
    const std::string& ans3)
    : m_difficulty(difficulty), m_categoryId(categoryId), m_question(question)
{
    m_possibleAnswers.push_back(correctAnswer);
    m_possibleAnswers.push_back(ans1);
    m_possibleAnswers.push_back(ans2);
    m_possibleAnswers.push_back(ans3);
}

std::string Question::getQuestion()
{
	return m_question;
}

std::vector<std::string> Question::getPossibleAnswers()
{
	return m_possibleAnswers;
}

int Question::getCorrectAnswerId()
{
    return 0;
}
