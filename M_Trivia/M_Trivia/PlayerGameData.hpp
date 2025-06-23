#pragma once
#include <chrono>

class PlayerGameData {
public:
    Question question;
    bool m_isActive;
    bool answeredLastQuestion;

    PlayerGameData() = default;
    PlayerGameData(const Question& q)
        : question(q), answeredLastQuestion(false), m_isActive(true)
    {
    }
};
