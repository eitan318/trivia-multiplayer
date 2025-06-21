#pragma once
#include "CreateRoomResponseErrors.hpp"
#include "Room.hpp"
#include "Game.hpp"
#include "GameManager.hpp"
#include "GeneralResponseErrors.hpp"
#include <mutex>
#include <vector>

/**
 * @brief Manages the lifecycle of rooms in the application.
 */
class VSManager : public GameManager
{
private:
    static unsigned int ids;     ///< Counter for generating unique room IDs.
    std::map<LoggedUser, bool> m_waitingList;
    mutable std::mutex m_waitingListMutex;
    const RoomPreview defaultRoomPreview;

    /**
     * @brief Constructs a RoomManager instance.
     * @param database Reference to the database interface.
     */
    VSManager();

    /**
     * @brief Destructor for cleaning up resources.
     */
    ~VSManager();

    // Disable copy constructor and assignment operator to enforce singleton pattern.
    VSManager(const VSManager&) = delete;
    VSManager& operator=(const VSManager&) = delete;

public:
    /**
     * @brief Retrieves the singleton instance of VSManager.
     * @param database Reference to the database interface.
     * @return A reference to the VSManager instance.
     */
    static VSManager& getInstance();

    GeneralResponseErrors joinWaitingList(const LoggedUser& loggedUser);

    GeneralResponseErrors leaveWaitingList(const LoggedUser& loggedUser);

    std::pair<GeneralResponseErrors, bool> didPlayerFoundMatch(const LoggedUser& loggedUser) const;

    GeneralResponseErrors startGame(const std::vector<LoggedUser>& players);

};
