#include "StartGameResponseErrors.hpp"

bool StartGameResponseErrors::noErrors() const
{
    return generalError.empty();
}

nlohmann::json StartGameResponseErrors::getJson() const
{
    nlohmann::json j = nlohmann::json{
        {"GeneralError", generalError},
    };
    return j;
}
