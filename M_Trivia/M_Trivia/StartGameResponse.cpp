#include "StartGameResponse.hpp"


StartGameResponse::StartGameResponse(StartGameResponseErrors* errors) : 
	Response(errors)
{
}

ResponseCodes StartGameResponse::getCode() const
{
	return ResponseCodes::C_StartGameResponse;
}
