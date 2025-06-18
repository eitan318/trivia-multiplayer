#pragma once
#include "Response.hpp"
#include "CreateRoomResponseErrors.hpp"
#include "RoomData.hpp"

/**
 * @class CreateRoomResponse
 * @brief Represents a response for creating a room, including errors and room data.
 */
class CreateRoomResponse : public  Response<ResponseCodes::C_CreateRoomResponse, CreateRoomResponseErrors> {
private:
    RoomData roomData;

public:
    /**
        * @brief Constructor for CreateRoomResponse.
        * @param errors The error details for the response.
        * @param roomData The room data associated with the response.
        */
    CreateRoomResponse(std::unique_ptr<CreateRoomResponseErrors> errors, const RoomData& roomData);

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const override;
};
