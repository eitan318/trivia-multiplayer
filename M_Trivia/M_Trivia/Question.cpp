#include "Question.hpp"
#include <random>

QuestionDifficultyLevelScores Question::getMatchingDifficultyLevel(const std::string& difficultyStr)
{
    if (difficultyStr == "easy") {
        return QuestionDifficultyLevelScores::Easy;
    }
    else if (difficultyStr == "medium") {
        return QuestionDifficultyLevelScores::Medium;
    }
    else if (difficultyStr == "hard") {
        return QuestionDifficultyLevelScores::Hard;
    }
    else {
        throw std::invalid_argument("Invalid difficulty level: " + difficultyStr);
    }
}

Question::Question(unsigned int id, const std::string& difficulty, const std::string& category, const std::string& question,
    const std::string& correctAnswer, const std::string& ans1, const std::string& ans2,
    const std::string& ans3)
    :  m_id(id), m_difficultyStr(difficulty), m_difficulty(getMatchingDifficultyLevel(difficulty)), m_category(category), m_question(question)
{

    // Add answers to the vector
    m_possibleAnswers.push_back(correctAnswer);
    m_possibleAnswers.push_back(ans1);
    m_possibleAnswers.push_back(ans2);
    m_possibleAnswers.push_back(ans3);

    // Shuffle the answers while tracking the index of the correct answer
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<int> indices = { 0, 1, 2, 3 }; // Track original indices
    std::shuffle(indices.begin(), indices.end(), g);

    // Reorder answers and update the correct answer index
    std::vector<std::string> shuffledAnswers(4);
    for (size_t i = 0; i < indices.size(); ++i) {
        shuffledAnswers[i] = m_possibleAnswers[indices[i]];
        if (indices[i] == 0) { // Original index of the correct answer
            m_correctAnswerIdx = i;
        }
    }
    m_possibleAnswers = shuffledAnswers;
}

unsigned int Question::getId() const
{
    return this->m_id;
}

std::string Question::getQuestion() const
{
    return m_question;
}

std::vector<std::string> Question::getPossibleAnswers() const
{
    return m_possibleAnswers;
}

int Question::getCorrectAnswerId() const
{
    return m_correctAnswerIdx;
}

QuestionDifficultyLevelScores Question::getDifficultyLevel()
{
    return m_difficulty;
}
