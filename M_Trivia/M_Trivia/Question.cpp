#include "Question.hpp"
#include <random>
#include <stdexcept>

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
    : m_id(id), m_difficultyStr(difficulty), m_difficulty(getMatchingDifficultyLevel(difficulty)), m_category(category), m_question(question)
{
    // Add answers to the vector
    m_possibleAnswers.push_back(correctAnswer);
    m_possibleAnswers.push_back(ans1);
    m_possibleAnswers.push_back(ans2);
    m_possibleAnswers.push_back(ans3);

    m_originalToShuffledMap = { 0, 1, 2, 3 };
}

void Question::shuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(m_originalToShuffledMap.begin(), m_originalToShuffledMap.end(), g);

    std::vector<std::string> shuffledAnswers(4);
    for (size_t i = 0; i < m_originalToShuffledMap.size(); ++i) {
        shuffledAnswers[i] = m_possibleAnswers[m_originalToShuffledMap[i]];
        if (m_originalToShuffledMap[i] == 0) { 
            m_correctAnswerIdx = i;
        }
    }

    m_possibleAnswers = shuffledAnswers;
}


Question::Question(const Question& other)
    : m_id(other.m_id),
    m_difficultyStr(other.m_difficultyStr),
    m_difficulty(other.m_difficulty),
    m_category(other.m_category),
    m_question(other.m_question),
    m_possibleAnswers(other.m_possibleAnswers),
    m_originalToShuffledMap(other.m_originalToShuffledMap),
    m_correctAnswerIdx(other.m_correctAnswerIdx)
{
}

unsigned int Question::getId() const
{
    return this->m_id;
}

int Question::getOriginalAnswerNum(int shuffledAnswerId) const
{
    if (shuffledAnswerId < 0 || shuffledAnswerId >= m_originalToShuffledMap.size()) {
        throw std::out_of_range("Invalid shuffledAnswerId");
    }

    // Find the original index that maps to the given shuffled index
    for (size_t originalIdx = 0; originalIdx < m_originalToShuffledMap.size(); ++originalIdx) {
        if (m_originalToShuffledMap[originalIdx] == shuffledAnswerId) {
            return originalIdx;
        }
    }

    throw std::logic_error("Mapping inconsistency detected");
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
