#pragma once
#include <string>

/**
 * @struct UserRecord
 * @brief Represents a user's personal information and credentials.
 */
struct UserRecord {
    std::string username;      
    std::string password;      
    std::string email;         
    std::string houseAddress;  
    std::string phoneNumber;
    std::string birthDate;    

    UserRecord() = default;

    /**
     * @brief Parameterized constructor for UserRecord.
     * @param username The username of the user.
     * @param password The user's password.
     * @param email The user's email address.
     * @param houseAddress The user's residential address.
     * @param phoneNumber The user's phone number.
     * @param birthDate The user's date of birth.
     */
    UserRecord(const std::string& username,
        const std::string& password,
        const std::string& email,
        const std::string& houseAddress,
        const std::string& phoneNumber,
        const std::string& birthDate)
        : username(username),
        password(password),
        email(email),
        houseAddress(houseAddress),
        phoneNumber(phoneNumber),
        birthDate(birthDate) {
    }
};
