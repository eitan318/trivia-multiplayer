#include "VSManager.hpp"

VSManager::VSManager() 
{
}

VSManager::~VSManager()
{
}


VSManager& VSManager::getInstance()
{
    static VSManager instance;
    return instance;
}


GeneralResponseErrors VSManager::joinWaitingList(const LoggedUser& loggedUser)
{
    GeneralResponseErrors errors;
    std::lock_guard<std::mutex> lock(this->m_waitingListMutex);
    this->m_waitingList.emplace(loggedUser, false);
    return errors;
}

GeneralResponseErrors VSManager::leaveWaitingList(const LoggedUser& loggedUser)
{
    std::lock_guard<std::mutex> lock(this->m_waitingListMutex);

    auto it = this->m_waitingList.find(loggedUser);
    if (it != this->m_waitingList.end()) {
        this->m_waitingList.erase(it);
        return GeneralResponseErrors{}; // No error
    }

    return GeneralResponseErrors{ "User not found in waiting list" }; // Return error
}

std::pair<GeneralResponseErrors, bool> VSManager::didPlayerFoundMatch(const LoggedUser& loggedUser) const
{
    std::lock_guard<std::mutex> lock(this->m_waitingListMutex);

    auto it = this->m_waitingList.find(loggedUser);
    if (it != this->m_waitingList.end()) {
        return { GeneralResponseErrors{}, it->second }; // No error, return match status
    }

    return { GeneralResponseErrors("User not found in waiting list"), false }; // Return error and default match status
}



//start game

//GeneralResponseErrors errors;
//std::shared_ptr<Game> game = createGame(this->defaultRoomPreview);
//for (LoggedUser user : players) {
//    game->join(user);
//}
//return errors;
