#include "CreateRoomResponseErrors.hpp"

bool CreateRoomResponseErrors::noErrors() const {
  return questionCountError.empty();
}

nlohmann::json CreateRoomResponseErrors::getJson() const {
  nlohmann::json j;
  j["QuestionCountError"] = questionCountError;
  return j;
}
