#pragma once
#include "Response.hpp"
#include "RoomData.hpp"
#include "LoggedUser.hpp"
#include <vector>

/**
 * @class GetRoomStateResponse
 * @brief Represents a response for geting a room's state.
 */
class GetRoomStateResponse : public Response {
private:
    bool m_hasGameBegun;
    const std::vector<LoggedUser>& m_players;
    unsigned int m_answerCount;
    double m_answerTimeOut;


public:
    /**
	* @brief Constructor for CreateRoomResponse.
	* @param errors The error details for the response.
	*/
    GetRoomStateResponse(
        unsigned int status,
		bool hasGameBegun,
		const std::vector<LoggedUser>& players,
		unsigned int answerCount,
		double answerTimeOut);


    /**
     * @brief Deleted default constructor to enforce proper initialization.
     */
    GetRoomStateResponse() = delete;

    /**
     * @brief Gets the response code for this response.
     * @return The response code as an unsigned integer.
     */
    ResponseCodes getCode() const override;

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const override;
};
