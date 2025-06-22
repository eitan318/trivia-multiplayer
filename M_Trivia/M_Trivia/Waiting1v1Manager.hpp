#pragma once
#include "Room.hpp"
#include "Game.hpp"
#include "GameManager.hpp"
#include "GeneralResponseErrors.hpp"
#include <mutex>
#include <vector>

/**
 * @brief Manages the lifecycle of rooms in the application.
 */
class Waiting1v1Manager
{
private:
    static unsigned int ids;     ///< Counter for generating unique room IDs.
    std::map<LoggedUser, bool> m_waitingList;
    mutable std::mutex m_waitingListMutex;
    RoomPreview* defaultRoomPreview;

    /**
     * @brief Constructs a RoomManager instance.
     * @param database Reference to the database interface.
     */
    Waiting1v1Manager();

    /**
     * @brief Destructor for cleaning up resources.
     */
    ~Waiting1v1Manager();

    // Disable copy constructor and assignment operator to enforce singleton pattern.
    Waiting1v1Manager(const Waiting1v1Manager&) = delete;
    Waiting1v1Manager& operator=(const Waiting1v1Manager&) = delete;

public:
    /**
     * @brief Retrieves the singleton instance of VSManager.
     * @param database Reference to the database interface.
     * @return A reference to the VSManager instance.
     */
    static Waiting1v1Manager& getInstance();

    GeneralResponseErrors joinWaitingList(const LoggedUser& loggedUser);

    GeneralResponseErrors leaveWaitingList(const LoggedUser& loggedUser);

    std::pair<GeneralResponseErrors, bool> didPlayerFoundMatch(const LoggedUser& loggedUser) const;

};