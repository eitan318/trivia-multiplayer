#include "SignupRequest.hpp"

SignupRequest::SignupRequest(const nlohmann::json& j) {
	const std::string username = j.at("Username");
	const std::string password = j.at("Password");
	const std::string email = j.at("Email");
	const std::string address = j.at("HouseAddress");
	const std::string phone = j.at("PhoneNumber");
	const std::string birthDate = j.at("BirthDate");

	this->userRecord = UserRecord(username, password, email, address, phone, birthDate);
}
    
const UserRecord& SignupRequest::getUserRecord() const
{
	return userRecord; 
}
