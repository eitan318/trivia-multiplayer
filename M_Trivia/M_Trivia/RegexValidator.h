#pragma once 
#include <string>
#include <regex>
class RegexValidator {
public:
	static bool validEmail(const std::string&);
	static bool validPhoneNumber(const std::string&);
	static bool validUsername(const std::string&);
	static bool validPassword(const std::string&);
	static bool validHouseAddress(const std::string&);
	static bool validBirthDate(const std::string&);
};