#include "LoginRequest.hpp"

LoginRequest::LoginRequest(const nlohmann::json& j) :
    username(j.at("Username")),
    password(j.at("Password"))
{
}



const std::string& LoginRequest::getUsername() const 
{
	return username; 
}


const std::string& LoginRequest::getPassword() const
{
	return password;
}
