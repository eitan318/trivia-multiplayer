#pragma once 
#include "json.hpp"


enum ResponsesCodes {
	C_ErrorResponse = 0,
	C_NoDataResponse = 1,
	C_GetRoomsResponse = 2,
	C_GetPlayersInRoomResponse = 3,
	C_GetHighScoreResponse = 4,
	C_GetPersonalStatsResponse = 5,
	C_SendPasswordResetCodeResponse = 6,

};


class Response {
public:

	/**
	 * @brief Gets the response code for this response.
	 * @return The response code as an unsigned integer.
	 */
	virtual unsigned int getCode() const = 0;

	/**
	 * @brief Converts the response to a JSON object.
	 * @return A JSON representation of the response.
	 */
	virtual  nlohmann::json getJson() const = 0;
};