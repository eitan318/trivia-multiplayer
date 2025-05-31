#include "CloseRoomResponseErrors.hpp"

bool CloseRoomResponseErrors::noErrors() const
{
    return this->generalError.empty();
}

nlohmann::json CloseRoomResponseErrors::getJson() const
{
    nlohmann::json j = nlohmann::json{
        {"GeneralError", generalError},
    };
    return j;
}
