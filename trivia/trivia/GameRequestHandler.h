#pragma once
#include "IRequestHandler.h"
#include "Game.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "json.hpp"

class GameRequestHandler : IRequestHandler
{
private:
	Game& m_game;
	LoggedUser* m_user;
	GameManager* m_gameManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult getQuestion(RequestInfo& request);
	RequestResult submitAnswer(RequestInfo& request);
	RequestResult getGameResults(RequestInfo& request);
	RequestResult leaveGame(RequestInfo& request);
public:
	bool isRequestRelevant(const RequestInfo& request) override;
	RequestResult handleRequest(RequestInfo& request) override;
	GameRequestHandler(Game& game, LoggedUser* user, GameManager* gameManager, RequestHandlerFactory& handlerFactory);
};

