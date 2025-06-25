#pragma once
#include "Room.hpp"
#include "Game.hpp"
#include "GameManager.hpp"
#include "GeneralResponseErrors.hpp"
#include "RoomPreview.hpp"
#include <mutex>
#include <vector>
#include <tuple>



/**
 * @brief Manages the lifecycle of rooms in the application.
 */
class Waiting1v1Manager
{
private:
    static unsigned int ids;     ///< Counter for generating unique room IDs.
    std::vector<LoggedUser> m_waitingList;
    std::map<LoggedUser, std::pair<std::shared_ptr<Game>, std::shared_ptr<RoomPreview>>> m_matchedPlayers;
    mutable std::mutex m_waitingListMutex;
    RoomPreview m_gameRoomPreview;
    GameManager& m_gameManager;
    std::condition_variable m_condition;
    std::atomic<bool> m_running;
    std::thread m_workerThread;

    /**
     * @brief Constructs a Waiting1v1Manager instance.
     * @param database Reference to the database interface.
     */
    Waiting1v1Manager(GameManager& gameManager);

    /**
     * @brief Destructor for cleaning up resources.
     */
    ~Waiting1v1Manager();

    // Disable copy constructor and assignment operator to enforce singleton pattern.
    Waiting1v1Manager(const Waiting1v1Manager&) = delete;
    Waiting1v1Manager& operator=(const Waiting1v1Manager&) = delete;


    void processingPlayers();

public:
    /**
     * @brief Retrieves the singleton instance of VSManager.
     * @param database Reference to the database interface.
     * @return A reference to the VSManager instance.
     */
    static Waiting1v1Manager& getInstance(GameManager& gameManager);

    GeneralResponseErrors joinWaitingList(const LoggedUser& loggedUser);



    GeneralResponseErrors leaveWaitingList(const LoggedUser& loggedUser);

    RoomData getDefault1v1GameSettings();

    std::tuple<GeneralResponseErrors, std::shared_ptr<Game>, std::shared_ptr<RoomPreview>> didPlayerFoundMatch(const LoggedUser& loggedUser);




};