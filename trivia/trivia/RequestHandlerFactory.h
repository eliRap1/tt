#pragma once
#include "LoginManager.h"
#include "StatisticsManager.h"
#include "RoomManager.h"

class RequestHandlerFactory
{
private:
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	StatisticsManager m_StatisticsManager;

public:
	RequestHandlerFactory(IDatabase* database);
	LoginManager& getLoginManager();
	IRequestHandler* createLoginRequestHandler();
};

