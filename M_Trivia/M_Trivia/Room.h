#pragma once
#include "RoomData.h"
#include "LoggedUser.h"
#include <vector>

/**
 * @class Room
 * @brief Represents a chat or game room with metadata and a list of users.
 */
class Room {
private:
    static unsigned int id;            
    RoomData m_metadata;               
    std::vector<LoggedUser> m_users;   

public:
    /**
     * @brief Constructs a Room with metadata and an initial user.
     * @param roomdata The metadata associated with the room.
     * @param user The initial user to add to the room.
     */
    Room(RoomData& roomdata, LoggedUser& user);

    /**
     * @brief Default constructor for creating an empty Room.
     */
    Room();

    /**
     * @brief Destructor for cleaning up the Room object.
     */
    ~Room();

    /**
     * @brief Adds a user to the room.
     * @param loggeduser The user to be added to the room.
     */
    void addUser(LoggedUser& loggeduser);

    /**
     * @brief Removes a user from the room.
     * @param loggeduser The user to be removed from the room.
     */
    void removeUser(LoggedUser& loggeduser);

    /**
     * @brief Retrieves the usernames of all users in the room.
     * @return A vector of strings containing the usernames of all users.
     */
    std::vector<std::string> getAllUsers() const;

    /**
     * @brief Retrieves the metadata associated with the room.
     * @return The RoomData object containing the room's metadata.
     */
    RoomData getRoomData() const;

    /**
     * @brief Updates the metadata of the room.
     * @param roomdata The new RoomData object to set as the room's metadata.
     */
    void setRoomData(RoomData& roomdata);
};
