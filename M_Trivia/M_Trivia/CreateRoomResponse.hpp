#pragma once
#include "json.hpp"
#include "Response.hpp"

/**
 * @class CreateRoomResponse
 * @brief Represents a response containing Status only and no data
 */
class CreateRoomResponse : public Response {
private:
    RoomData roomData;

public:
    CreateRoomResponse() = delete;

    CreateRoomResponse(unsigned int status, const RoomData& roomData)
        : Response(status), roomData(roomData) {
    }

    /**
     * @brief Gets the response code for this response.
     * @return The response code as an unsigned integer.
     */
    unsigned char getCode() const override { return C_CreateRoomResponse; }

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const override {
        nlohmann::json j = baseJson();  // Assuming baseJson is defined in the base class
        j["RoomData"] = roomData;
        return j;
    }

};
