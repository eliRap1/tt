#pragma once
#include <string>
#include "json.hpp"
#include <iostream>
using json = nlohmann::json;
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

typedef struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int QuestionsCount;
	unsigned int answerTimeout;
} CreateRoomRequest;

typedef struct GetPlayerInRoomRequest
{
	unsigned int roomId;
} GetPlayerInRoomRequest;

typedef struct JoinRoomRequest
{
	unsigned int roomId;
} JoinRoomRequest;
class JsonRequestPacketDeserializer
{
public:
	
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<unsigned char> buffer);
	static GetPlayerInRoomRequest deserializeGetPlayerInRoomRequest(std::vector<unsigned char> buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<unsigned char> buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<unsigned char> buffer);
};

