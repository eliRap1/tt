#pragma once
#include <string>
#include "json.hpp"
#include <iostream>
#include <vector>
using json = nlohmann::json;

// --- ENUMS FOR RESPONSE CODES ---
enum ResponseCode {
	LOGIN_CODE = 1,
	SIGNUP_CODE = 2,
	ERROR_CODE = 3,
	LOGOUT_CODE = 4,
	GET_ROOMS_CODE = 5,
	GET_PLAYERS_IN_ROOM_CODE = 6,
	JOIN_ROOM_CODE = 7,
	CREATE_ROOM_CODE = 8,
	HIGH_SCORE_CODE = 9,
	PERSONAL_STATS_CODE = 10
};

// --- REQUEST STRUCTS ---

typedef struct LoginResponse {
	unsigned int status;
} LoginResponse;

typedef struct SignupResponse {
	unsigned int status;
} SignupResponse;
typedef struct LoginRequest
{
	std::string username;
	std::string password;
} LoginRequest;

typedef struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
} SignupRequest;

typedef struct LogoutResponse {
	unsigned int status;
} LogoutResponse;

typedef struct GetRoomResponse {
	unsigned int status;
	std::vector<json> rooms;
} GetRoomResponse;

typedef struct GetPlayersInRoomResponse {
	std::vector<std::string> players;
} GetPlayersInRoomResponse;

typedef struct JoinRoomResponse {
	unsigned int status;
} JoinRoomResponse;

typedef struct CreateRoomResponse {
	unsigned int status;
} CreateRoomResponse;

typedef struct getHighScoresResponse {
	unsigned int status;
	std::vector<std::string> highScores;
} getHighScoresResponse;

typedef struct getPersonalStatsResponse {
	unsigned int status;
	std::vector<std::string> statistics;
} getPersonalStatsResponse;

typedef struct ErrorResponse {
	std::string message;
} ErrorResponse;
class JsonResponsePacketSerializer
{
public:
	static std::vector<unsigned char> serializeResponse(const ErrorResponse&);
	static std::vector<unsigned char> serializeResponse(const LoginResponse&);
	static std::vector<unsigned char> serializeResponse(const SignupResponse&);
	static std::vector<unsigned char> serializeResponse(const LogoutResponse&);
	static std::vector<unsigned char> serializeResponse(const GetRoomResponse&);
	static std::vector<unsigned char> serializeResponse(const GetPlayersInRoomResponse&);
	static std::vector<unsigned char> serializeResponse(const JoinRoomResponse&);
	static std::vector<unsigned char> serializeResponse(const CreateRoomResponse&);
	static std::vector<unsigned char> serializeResponse(const getHighScoresResponse&);
	static std::vector<unsigned char> serializeResponse(const getPersonalStatsResponse&);
};
