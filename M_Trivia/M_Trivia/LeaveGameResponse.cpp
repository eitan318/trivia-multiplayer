#include "LeaveGameResponse.hpp"

LeaveGameResponse::LeaveGameResponse(GeneralResponseErrors* errors) :
    Response(errors)
{
}

ResponseCodes LeaveGameResponse::getCode() const
{
    return ResponseCodes::C_LeaveGameResponse;
}
