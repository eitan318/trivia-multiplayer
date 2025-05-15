#include "JoinRoomResponseErrors.hpp"

bool JoinRoomResponseErrors::noErrors() const { return generalError.empty(); }

nlohmann::json JoinRoomResponseErrors::getJson() const {
  nlohmann::json j;
  j["GeneralError"] = generalError;
  return j;
}
