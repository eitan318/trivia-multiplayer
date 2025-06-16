#pragma once
#include "CreateRoomResponseErrors.hpp"
#include "IDatabase.hpp"
#include "Room.hpp"
#include "RoomPreview.hpp"
#include "GeneralResponseErrors.hpp"
#include <mutex>
#include <vector>

/**
 * @brief Manages the lifecycle of rooms in the application.
 */
class RoomManager
{
private:
    static unsigned int ids;     ///< Counter for generating unique room IDs.
    std::vector<Room> m_rooms; 
    mutable std::mutex m_roomsMutex;
    IDatabase& m_database;       ///< Pointer to the database interface for accessing data.

    /**
     * @brief Constructs a RoomManager instance.
     * @param database Reference to the database interface.
     */
    RoomManager(IDatabase& database);

    /**
     * @brief Destructor for cleaning up resources.
     */
    ~RoomManager();

    // Disable copy constructor and assignment operator to enforce singleton pattern.
    RoomManager(const RoomManager&) = delete;
    RoomManager& operator=(const RoomManager&) = delete;

public:
    /**
     * @brief Retrieves the singleton instance of RoomManager.
     * @param database Reference to the database interface.
     * @return A reference to the RoomManager instance.
     */
    static RoomManager& getInstance(IDatabase& database);

    /**
     * @brief Creates a new room. I set the id in room data
     * @param player The user creating the room.
     * @param roomData The data defining the room's properties.
     */
    CreateRoomResponseErrors createRoom(const LoggedUser& player, RoomData& roomData);

    /**
     * @brief join an existing room. I set the id in room data
     * @param loggedUser The user joining the room.
     * @param id The id of the room to join.
     */
    GeneralResponseErrors joinRoom(unsigned int id, const LoggedUser& loggedUser);

    /**
     * @brief Deletes an existing room by its ID.
     * @param ID The ID of the room to delete.
     */
    void deleteRoom(int ID);
    /**
     * @brief Retrieves a list of all active rooms.
     * @return A vector of RoomData objects representing active rooms.
     */
    std::vector<RoomPreview> getRooms() const;

    /**
	 * Attempts to close the current room.
	 *
	 * @return A CloseRoomResponseErrors indicating the result of the operation.
	 */
    GeneralResponseErrors closeRoom(unsigned int roomId, const LoggedUser& closer);

    /**
     * Attempts to start the game in the current room.
     *
     * @return A StartGameResponseErrors indicating the result of the operation.
     */
    GeneralResponseErrors startGameOfRoom(unsigned int roomId);

    /**
     * @brief Retrieves a reference to a specific room.
     * @param ID The ID of the room to retrieve.
     * @return A reference to the Room object.
     * @throws MyException if the room does not exist.
     */
    Room* getRoom(int ID);


    void leaveRoom(unsigned int roomId,
        const LoggedUser& loggedUser);
};
