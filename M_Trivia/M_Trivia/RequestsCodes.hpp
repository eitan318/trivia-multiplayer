#pragma once
enum class RequestsCodes : unsigned char {
	LoginRequest = 1,
	SignupRequest = 2,
	CreateRoomRequest = 3,
	GetPlayersInRoomRequest = 4,
	JoinRoomRequest = 5,
	SendPasswordResetCodeRequest = 6,
	ResetPasswordRequest = 7,
	GetHighScoreRequest = 8
};








