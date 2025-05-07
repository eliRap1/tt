#pragma once
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"
class MenuRequestHandler : public IRequestHandler
{
private:
	LoggedUser m_loggedUser;
	RequestHandlerFactory& m_handlerFactory;

public:
	bool isRequestRelevant(RequestInfo& request) override;
	RequestResult handleRequest(RequestInfo& request) override;
private:
	RequestResult signout(RequestInfo& request);
	RequestResult getRooms(RequestInfo& request);
	RequestResult createRoom(RequestInfo& request);
	RequestResult joinRoom(RequestInfo& request);
	RequestResult getPlayerInRoom(RequestInfo& request);
	RequestResult getPersonalStats(RequestInfo& request);
	RequestResult getHighScores(RequestInfo& request);
};

