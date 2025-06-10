#pragma once
#include <vector>
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
class IRequestHandler;
typedef struct RequestInfo
{
	unsigned char id;
	time_t receivalTime;
	std::vector<unsigned char> buffer;
} RequestInfo;

typedef struct RequestResult 
{
	std::vector<unsigned char> response;
	IRequestHandler* newHandler;
} RequestResult;
typedef enum GameStates { ADMIN_LEFT , WAIT_FOR_PLAYERS, START };
static GameStates gameState = WAIT_FOR_PLAYERS;
class IRequestHandler
{
public:
	virtual bool isRequestRelevant(const RequestInfo& request) = 0;
	virtual RequestResult handleRequest(RequestInfo& request) = 0;
};
