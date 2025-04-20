#pragma once
#include "RegexValidator.h"

bool RegexValidator::validEmail(const std::string& email)
{
	std::regex emailRegex(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.(com|co\.il|cyber\.org\.il)$)");
    return std::regex_match(email, emailRegex);
}

bool RegexValidator::validPhoneNumber(const std::string& phoneNumber)
{
    std::regex phoneRegex(R"(^0(2|3|4|5\d)-\d{7}$)");
    return std::regex_match(phoneNumber, phoneRegex);
}

bool RegexValidator::validUsername(const std::string&)
{
    return true;
}

bool RegexValidator::validPassword(const std::string& password)
{
    std::regex passwordRegex(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[!@#$%^&*]).{8,}$)");
    return std::regex_match(password, passwordRegex);
}

bool RegexValidator::validHouseAddress(const std::string& houseAddress)
{
    std::smatch match;
    std::regex addressRegex(R"(^([A-Za-z\s]+),\s*(\d+),\s*([A-Za-z\s]+)$)");
    return std::regex_match(houseAddress, match, addressRegex);
    std::string street = match[1];
    std::string apt = match[2];
    std::string city = match[3];
}

bool RegexValidator::validBirthDate(const std::string& birthDate)
{
    std::regex dateRegex(R"(^(0[1-9]|[12][0-9]|3[01])[-/.](0[1-9]|1[0-2])[-/.](19|20)\d{2}$)");
    return std::regex_match(birthDate, dateRegex);
}
