#include "StartGameResponse.hpp"

StartGameResponse::StartGameResponse(unsigned int status) :
	Response(status)
{
}

ResponseCodes StartGameResponse::getCode() const
{
	return ResponseCodes::C_StartGameResponse;
}
