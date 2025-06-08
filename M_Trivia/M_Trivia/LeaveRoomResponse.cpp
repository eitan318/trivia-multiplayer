#include "LeaveRoomResponse.hpp"


LeaveRoomResponse::LeaveRoomResponse(GeneralResponseErrors* errors) :
	Response(errors)
{

}

ResponseCodes LeaveRoomResponse::getCode() const
{
	return ResponseCodes::C_LeaveRoomResponse;
}
