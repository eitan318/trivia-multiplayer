#pragma once
#include "HighScoreInfo.hpp"
#include "Response.hpp"
#include <vector>
#include "Question.hpp"
#include "GeneralResponseErrors.hpp"


/**
 * @class GetHighScoreResponse
 * @brief Represents a response status, statistics
 */
class GetQuestionResponse : public Response<ResponseCodes::C_GetQuestionResponse, GeneralResponseErrors>  {
private:
    const std::optional<Question>& m_question;

public:
    GetQuestionResponse(std::unique_ptr<GeneralResponseErrors> errors, const std::optional<Question>& question);

    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const override;
};


