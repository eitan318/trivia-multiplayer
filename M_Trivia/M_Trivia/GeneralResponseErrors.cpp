#include "GeneralResponseError.hpp"

bool GeneralResponseErrors::noErrors() const
{
    return this->generalError.empty();
}

nlohmann::json GeneralResponseErrors::getJson() const
{
    nlohmann::json j;
    j["GeneralError"] = generalError;
    return j;
}
