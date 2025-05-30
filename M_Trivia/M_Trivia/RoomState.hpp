#pragma once
#include <vector>
#include "LoggedUser.hpp"

struct RoomState{
    RoomState(bool hasGameBegun, const std::vector<LoggedUser>& players, unsigned int answerCount, double answerTimeOut)
        : m_answerCount(answerCount),
        m_players(players),
        m_answerTimeOut(answerTimeOut),
        m_hasGameBegun(hasGameBegun)
    {}
    bool m_hasGameBegun;
    const std::vector<LoggedUser>& m_players;
    unsigned int m_answerCount;
    double m_answerTimeOut;
};

// Define a to_json function for RoomState
inline void to_json(nlohmann::json& j, const RoomState& roomState) {
    j = nlohmann::json{
        {"HasGameBegun", roomState.m_hasGameBegun},
        {"Players", roomState.m_players},
        {"AnswerCount", roomState.m_answerCount},
        {"AnswerTimeOut", roomState.m_answerTimeOut}
    };
}