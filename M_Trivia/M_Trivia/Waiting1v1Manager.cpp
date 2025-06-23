#include "Waiting1v1Manager.hpp"

Waiting1v1Manager::Waiting1v1Manager(GameManager& gameManager) : 
    m_gameManager(gameManager), m_workerThread(&Waiting1v1Manager::processingPlayers, this),
    m_gameRoomPreview(std::make_shared<RoomPreview>(
        RoomData{ 0,"1v1", 2, 10, 5, 2 },
        0,
        RoomStatus::NotInGame
    ))
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

        std::unique_lock<std::mutex> lock(this->m_waitingListMutex); // not guard allow conditional flow

        m_condition.wait(lock, [this]() {
            return !m_running || m_waitingList.size() >= 2;
            });

        if (!m_running) {
            break; 
        }

        std::shared_ptr<Game> game = this->m_gameManager.createGame(this->m_gameRoomPreview);

        if (this->m_waitingList.size() < 2) {
            continue;
        }

        auto it = this->m_waitingList.begin();
        LoggedUser user1 = it->first;
        m_waitingList.erase(it);
        it++;
        LoggedUser user2 = it->first;

        game->join(user1);
        game->join(user2);

        this->m_waitingList[user1] = game;
        this->m_waitingList[user2] = game;

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
        this->m_waitingList.emplace(loggedUser, nullptr);
    }
    m_condition.notify_one();
    return errors;
}

GeneralResponseErrors Waiting1v1Manager::leaveWaitingList(const LoggedUser& loggedUser)
{
	std::lock_guard<std::mutex> lock(this->m_waitingListMutex);

	auto it = this->m_waitingList.find(loggedUser);
	if (it != this->m_waitingList.end()) {
		this->m_waitingList.erase(it);
		m_condition.notify_one();
		return GeneralResponseErrors{}; 
	}

    return GeneralResponseErrors{ "User not found in waiting list" }; 
}

std::shared_ptr<RoomPreview> Waiting1v1Manager::getGameRoomPreview()
{
    return this->m_gameRoomPreview;
}

std::pair<GeneralResponseErrors, std::shared_ptr<Game>> Waiting1v1Manager::didPlayerFoundMatch(const LoggedUser& loggedUser) const
{
    std::lock_guard<std::mutex> lock(this->m_waitingListMutex);

    auto it = this->m_waitingList.find(loggedUser);
    if (it != this->m_waitingList.end()) {
        return { GeneralResponseErrors{}, it->second }; 
    }

    return { GeneralResponseErrors("User not found in waiting list"), nullptr }; // Return error and default match status
}


