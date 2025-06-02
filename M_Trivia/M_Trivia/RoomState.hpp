#pragma once
#include <vector>
#include "LoggedUser.hpp"
#include "RoomStatus.h"

struct RoomState{
    RoomState(RoomStatus roomStatus, const std::vector<LoggedUser>& players, unsigned int answerCount, double answerTimeOut)
        : m_answerCount(answerCount),
        m_players(players),
        m_answerTimeOut(answerTimeOut),
        m_roomStatus(roomStatus)
    {}
    bool m_roomStatus;
    const std::vector<LoggedUser>& m_players;
    unsigned int m_answerCount;
    double m_answerTimeOut;
};

// Define a to_json function for RoomState
inline void to_json(nlohmann::json& j, const RoomState& roomState) {
    j = nlohmann::json{
        {"HasGameBegun", roomState.m_roomStatus},
        {"Players", roomState.m_players},
        {"AnswerCount", roomState.m_answerCount},
        {"AnswerTimeOut", roomState.m_answerTimeOut}
    };
}