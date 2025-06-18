#pragma once
#include <string>
#include <nlohmann/json.hpp>

/**
 * @struct UserRecord
 * @brief Represents a user's personal information and credentials.
 */
struct UserRecord {
    std::string username;      ///< The username of the user
    std::string password;      ///< The user's password
    std::string email;         ///< The user's email address
    std::string houseAddress;  ///< The user's residential address
    std::string phoneNumber;   ///< The user's phone number
    std::string birthDate;     ///< The user's date of birth

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
     * @brief Populates a UserRecord object from a JSON object.
     * @param j JSON object containing the user data.
     */
    void from_json(const nlohmann::json& j) {
        username = j.at("Username").get<std::string>();
        password = j.at("Password").get<std::string>();
        email = j.at("Email").get<std::string>();
        houseAddress = j.at("HouseAddress").get<std::string>();
        phoneNumber = j.at("PhoneNumber").get<std::string>();
        birthDate = j.at("BirthDate").get<std::string>();
    }
};

