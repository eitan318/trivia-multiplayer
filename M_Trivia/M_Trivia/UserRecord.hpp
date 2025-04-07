#pragma once
#include <string>

struct UserRecord {
    std::string username;
    std::string password;
    std::string email;
    std::string houseAddress;
    std::string phoneNumber;
    std::string birthDate;

    UserRecord() = default;

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
