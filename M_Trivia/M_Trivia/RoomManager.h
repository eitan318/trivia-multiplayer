#pragma once
#include "Room.h"
#include "MyException.h"
#include "IDatabase.h"
#include <map>

/**
 * @brief Manages the lifecycle of rooms in the application.
 */
class RoomManager {
private:
    static unsigned int ids; ///< Counter for generating unique room IDs.
    std::map<int, Room> m_rooms; ///< Map of active rooms indexed by their ID.
    IDatabase& m_database; ///< Pointer to the database interface for accessing data.

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
     * @brief Retrieves the total number of questions available in the database.
     * @return The total count of questions.
     */
    unsigned int getTotalQuestionsCount() const;

    /**
     * @brief Creates a new room. I set the id in room data
     * @param player The user creating the room.
     * @param roomData The data defining the room's properties.
     */
    unsigned int createRoom(const LoggedUser& player, RoomData& roomData);

    /**
     * @brief Deletes an existing room by its ID.
     * @param ID The ID of the room to delete.
     */
    void deleteRoom(int ID);

    /**
     * @brief Retrieves the state of a room.
     * @param ID The ID of the room.
     * @return `true` if the room is active, `false` otherwise.
     */
    bool getRoomState(int ID);

    /**
     * @brief Retrieves a list of all active rooms.
     * @return A vector of RoomData objects representing active rooms.
     */
    std::vector<RoomData> getRooms();

    /**
     * @brief Retrieves a reference to a specific room.
     * @param ID The ID of the room to retrieve.
     * @return A reference to the Room object.
     * @throws MyException if the room does not exist.
     */
    Room& getRoom(int ID);
};
