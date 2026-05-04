#pragma once
#include <chrono>
#include "LastAnswerState.hpp"

class PlayerGameData {
public:
    Question question;
    bool m_isActive;
    LastAnswerState lastAnswerState;

    PlayerGameData() = default;
    PlayerGameData(const Question& q)
        : question(q), lastAnswerState(LastAnswerState::NoAnswer), m_isActive(true)
    {
    }
};
