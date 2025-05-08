#pragma once
#include "LoginManager.h"
#include "IDatabase.h"
#include "RoomManager.h"

class RequestHandlerFactory
{
private:
	LoginManager m_loginManager;
	IDatabase* m_database;
	RoomManager m_roomManager;

public:
	RequestHandlerFactory(IDatabase* database);
	LoginManager& getLoginManager();
	IRequestHandler* createLoginRequestHandler();
};

