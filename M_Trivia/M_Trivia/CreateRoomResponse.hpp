#pragma once
#include "json.hpp"
#include "Response.hpp"
#include "CreateRoomResponseErrors.hpp"
#include "RoomData.hpp"

/**
 * @class CreateRoomResponse
 * @brief Represents a response for creating a room, including errors and room data.
 */
class CreateRoomResponse : public Response {
private:
    RoomData roomData;

public:
    /**
        * @brief Constructor for CreateRoomResponse.
        * @param errors The error details for the response.
        * @param roomData The room data associated with the response.
        */
    CreateRoomResponse(CreateRoomResponseErrors* errors, const RoomData& roomData)
        : Response(errors), roomData(roomData) {
    }

    /**
     * @brief Deleted default constructor to enforce proper initialization.
     */
    CreateRoomResponse() = delete;

    /**
     * @brief Gets the response code for this response.
     * @return The response code as an unsigned integer.
     */
    ResponseCodes getCode() const override { return ResponseCodes::C_CreateRoomResponse; }

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const override {
        nlohmann::json j = baseJson();
        j["RoomData"] = roomData;
        return j;
    }
};
