#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "RoomManager.h"
class RequestHandlerFactory
{
private:
	LoginManager m_loginManager;
	IDatabase* m_database;
	RoomManager m_roomManager;

public:
	RequestHandlerFactory(IDatabase* database) : m_loginManager(database), m_database(database) {}
	LoginManager& getLoginManager() { return this->m_loginManager; }
	LoginRequestHandler* createLoginRequestHandler();//return new LoginRequestHandler(m_loginManager); }
};

