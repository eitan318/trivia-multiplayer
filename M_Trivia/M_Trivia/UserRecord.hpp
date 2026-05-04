#pragma once
#include <string>
#include "json.hpp"

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

    /**
     * @brief Constructor from JSON object.
     * @param j The JSON object to initialize the UserRecord.
     */
    explicit UserRecord(const nlohmann::json& j) {
        j.at("Username").get_to(username);
        j.at("Password").get_to(password);
        j.at("Email").get_to(email);
        j.at("HouseAddress").get_to(houseAddress);
        j.at("PhoneNumber").get_to(phoneNumber);
        j.at("BirthDate").get_to(birthDate);
    }

};

/**
 * @brief Deserialize UserRecord from JSON.
 * @param j JSON object to deserialize from.
 * @param ur UserRecord instance to populate.
 */
inline void from_json(const nlohmann::json& j, UserRecord& ur) {
    j.at("Username").get_to(ur.username);
    j.at("Password").get_to(ur.password);
    j.at("Email").get_to(ur.email);
    j.at("HouseAddress").get_to(ur.houseAddress);
    j.at("PhoneNumber").get_to(ur.phoneNumber);
    j.at("BirthDate").get_to(ur.birthDate);
}
