#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"
class RequestHandlerFactory
{
private:
	LoginManager m_loginManager;
	IDatabase* m_database;

public:
	LoginManager& getLoginManager() { return this->m_loginManager; }
	LoginRequestHandler* createLoginRequestHandler();//return new LoginRequestHandler(m_loginManager); }
};

