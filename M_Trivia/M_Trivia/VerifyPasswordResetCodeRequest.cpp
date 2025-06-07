#include "VerifyPasswordResetCodeRequest.hpp"

VerifyPasswordResetCodeRequest::VerifyPasswordResetCodeRequest(
    const nlohmann::json& j)
    : codeFromClient(j.at("PasswordResetCode")) {
}

const std::string& VerifyPasswordResetCodeRequest::getCodeFromClient() const {
    return this->codeFromClient;
}
