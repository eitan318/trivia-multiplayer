#pragma once
#include <vector>
#include "LoggedUser.hpp"

struct RoomState {
    bool m_hasGameBegun;
    const std::vector<LoggedUser>& m_players;
    unsigned int m_answerCount;
    double m_answerTimeOut;
};