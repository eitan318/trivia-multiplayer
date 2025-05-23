#pragma once
#include "RoomData.hpp"
#include "LoggedUser.hpp"
#include "RoomPreview.hpp"
#include <map>
#include <string>

/**
 * @class Room
 * @brief Represents a chat or game room with metadata and a list of users.
 */
class Room {
private:
    static unsigned int id;            
    RoomData m_metadata;               
    std::map<std::string,LoggedUser> m_users;   

public:
    /**
     * @brief Constructs a Room with metadata and an initial user.
     * @param roomdata The metadata associated with the room.
     * @param user The initial user to add to the room.
     */
    Room(const RoomData& roomdata, const LoggedUser& user);

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
    void addUser(const LoggedUser& loggeduser);

    /**
     * @brief Removes a user from the room.
     * @param loggeduser The user to be removed from the room.
     */
    void removeUser(const LoggedUser& loggeduser);

    /**
     * @brief Retrieves the usernames of all users in the room.
     * @return A vector of strings containing the usernames of all users.
     */
    std::map<std::string,LoggedUser> getAllUsers() const;



    /**
     * @brief Updates the metadata of the room.
     * @param roomdata The new RoomData object to set as the room's metadata.
     */
    void setRoomData(const RoomData& roomdata);


    bool getRoomStatus() const;
    /**
     * @brief Retrieves the metadata associated with the room.
     * @return The RoomPreview object containing the room's metadata.
     */
    RoomPreview getRoomPreview() const;
};
