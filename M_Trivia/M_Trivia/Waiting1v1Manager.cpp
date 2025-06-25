#include "Waiting1v1Manager.hpp"

Waiting1v1Manager::Waiting1v1Manager(GameManager& gameManager) : 
    m_gameManager(gameManager), 
    m_workerThread(&Waiting1v1Manager::processingPlayers, this),
    m_gameRoomPreview(std::make_shared<RoomPreview>(
        RoomData{ 0,"1v1", 2, 10, 5, 2 },
        0,
        RoomStatus::NotInGame
    )),
    m_running(true),
    m_waitingList()

{
    


}

Waiting1v1Manager::~Waiting1v1Manager()
{
    {
        std::lock_guard<std::mutex> lock(this->m_waitingListMutex);
        m_running = false;
    }
    m_condition.notify_all(); // Wake up the thread
    if (m_workerThread.joinable()) {
        m_workerThread.join();
    }
}

void Waiting1v1Manager::processingPlayers()
{
    while (m_running) {
        std::unique_lock<std::mutex> lock(this->m_waitingListMutex); // Lock the mutex

        // Wait until the condition is met
        m_condition.wait(lock, [this]() {
            return !m_running || m_waitingList.size() >= 2;
            });

        if (!m_running) {
            break;
        }

        if (this->m_waitingList.size() < 2) {
            continue;
        }

        LoggedUser user1 = m_waitingList[0];
        LoggedUser user2 = m_waitingList[1];

        m_waitingList.erase(m_waitingList.begin());
        m_waitingList.erase(m_waitingList.begin());

        lock.unlock();

        std::shared_ptr<Game> game = this->m_gameManager.createGame(this->m_gameRoomPreview, true);

        game->join(user1);
        game->join(user2);

        this->m_matchedPlayers[user1] = game;
        this->m_matchedPlayers[user2] = game;
    }
}



Waiting1v1Manager& Waiting1v1Manager::getInstance(GameManager& gameManager)
{
    static Waiting1v1Manager instance(gameManager);
    return instance;
}


GeneralResponseErrors Waiting1v1Manager::joinWaitingList(const LoggedUser& loggedUser)
{
    GeneralResponseErrors errors;
    {
        std::lock_guard<std::mutex> lock(this->m_waitingListMutex);
        this->m_waitingList.emplace_back(loggedUser);
    }
    m_condition.notify_one();
    return errors;
}

GeneralResponseErrors Waiting1v1Manager::leaveWaitingList(const LoggedUser& loggedUser)
{
    std::lock_guard<std::mutex> lock(this->m_waitingListMutex);

    auto it = std::find(m_waitingList.begin(), m_waitingList.end(), loggedUser);

    if (it != m_waitingList.end()) {
        m_waitingList.erase(it);
        m_condition.notify_one();

        return GeneralResponseErrors{}; // No error
    }

    return GeneralResponseErrors{ "User not found in waiting list" }; // Return an error if the user is not found
}


std::shared_ptr<RoomPreview> Waiting1v1Manager::getDefault1v1GameSettings()
{
    return this->m_gameRoomPreview;
}

std::pair<GeneralResponseErrors, std::shared_ptr<Game>> Waiting1v1Manager::didPlayerFoundMatch(const LoggedUser& loggedUser)
{
    std::lock_guard<std::mutex> lock(this->m_waitingListMutex);

    auto it = this->m_matchedPlayers.find(loggedUser);
    if (it != this->m_matchedPlayers.end()) {
        std::shared_ptr<Game> game = it->second;
        this->m_matchedPlayers.erase(it);
        return { GeneralResponseErrors{}, game }; 
    }

    return { GeneralResponseErrors("User not found in waiting list"), nullptr }; // Return error and default match status
}


