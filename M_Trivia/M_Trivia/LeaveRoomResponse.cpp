#include "LeaveRoomResponse.hpp"

LeaveRoomResponse::LeaveRoomResponse(unsigned int status) :
	Response(status)
{

}

ResponseCodes LeaveRoomResponse::getCode() const
{
	return ResponseCodes::C_LeaveRoomResponse;
}
