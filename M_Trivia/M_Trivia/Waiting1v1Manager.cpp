#include "Waiting1v1Manager.hpp"

unsigned int Waiting1v1Manager::ids = 0;

Waiting1v1Manager::Waiting1v1Manager(GameManager& gameManager) :
    m_gameManager(gameManager),
    m_workerThread(&Waiting1v1Manager::processingPlayers, this),
    m_gameRoomPreview(RoomPreview(
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
        m_matchedPlayers.clear();
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


        RoomPreview gameRoomPreview(this->m_gameRoomPreview);
        gameRoomPreview.roomData.id = ids;
        ids += 2;
        std::shared_ptr<Game> game = this->m_gameManager.createGame(gameRoomPreview, true);
        std::shared_ptr<RoomPreview> roomPreview = std::make_shared<RoomPreview>(gameRoomPreview);


        game->join(user1);
        game->join(user2);

        this->m_matchedPlayers[user1] = std::pair<std::shared_ptr<Game>, std::shared_ptr<RoomPreview>>(game, roomPreview);
        this->m_matchedPlayers[user2] = std::pair<std::shared_ptr<Game>, std::shared_ptr<RoomPreview>>(game, roomPreview);
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
        if (m_matchedPlayers.find(loggedUser) != m_matchedPlayers.end()) {
            this->m_matchedPlayers.erase(loggedUser);
        }
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


RoomData Waiting1v1Manager::getDefault1v1GameSettings()
{
    return this->m_gameRoomPreview.roomData;
}


std::tuple<GeneralResponseErrors, std::shared_ptr<Game>, std::shared_ptr<RoomPreview>>
Waiting1v1Manager::didPlayerFoundMatch(const LoggedUser& loggedUser)
{
    std::lock_guard<std::mutex> lock(this->m_waitingListMutex);

    auto it = this->m_matchedPlayers.find(loggedUser);
    if (it != this->m_matchedPlayers.end()) {
        auto [game, roomPreview] = it->second; // Extract the pair
        return { GeneralResponseErrors{}, std::move(game), std::move(roomPreview) };
    }

    return { GeneralResponseErrors("User not found in waiting list"), nullptr, nullptr }; // Return error and default match status
}

