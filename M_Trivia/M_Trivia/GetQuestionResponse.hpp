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
class GetQuestionResponse : public Response {
private:
    const std::optional<Question>& m_question;

public:
    GetQuestionResponse(GeneralResponseErrors* errors, const std::optional<Question>& question);

    /**
     * @brief Gets the response code for this response.
     * @return The response code as an unsigned integer.
     */
    ResponseCodes getCode() const override;


    /**
     * @brief Converts the response to a JSON object.
     * @return A JSON representation of the response.
     */
    nlohmann::json getJson() const override;
};


