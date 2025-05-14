#include "Response.hpp"

Response::Response(IResponseErrors* errors)
        : errors(errors), status(this->errors->statusCode) 
{
}

Response::Response(unsigned int status) : errors(nullptr), status(status) 
{
}

nlohmann::json Response::getJson() const {
        nlohmann::json errorsJson = errors ? errors->getJson() : nlohmann::json();
        nlohmann::json j = nlohmann::json{
            {"Status", status},
            //{"Errors", errorsJson}
        };
        if (errors) {
            j["Errors"] = errorsJson;
        }
        return j;
}


