#pragma once
#include "RoomData.hpp"
#include "LoggedUser.hpp"
#include "RoomPreview.hpp"
#include <vector>
#include <string>
#include "RoomStatus.h"
#include "RoomState.hpp"




/**
 * @class Room
 * @brief Represents a chat or game room with metadata and a list of users.
 */
class Room {
private:
    RoomData m_metadata;               
    std::vector<LoggedUser> m_users;   
    RoomStatus status;

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
    const std::vector<LoggedUser>& getUsersVector() const;


    /**
     * @brief Initialy sets the metadata of the room.
     * @param roomdata The new RoomData object to set as the room's metadata.
     */
    void setRoomData(const RoomData& roomdata);

    bool gameStarted() const;

    // closes the room
    void close();

    // starting a game in the room
    void startGame();

    void enterGame();

    void closeGame();

    //returning the id of the room
    unsigned int getId() const;

    /**
     * Retrieves the current status of the room.
     *
     * @return A RoomStatus representing the room's current state.
     */
    RoomStatus getRoomStatus() const;

    RoomState getRoomState() const;


     /**
     * @brief Retrieves the metadata associated with the room.
     * @return The RoomPreview object containing the room's metadata.
     */
    RoomPreview getRoomPreview() const;

    bool hasUser(const LoggedUser& user) const;

    bool isAdmin(const LoggedUser& username) const;
};
