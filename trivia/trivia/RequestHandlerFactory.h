#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"

class RequestHandlerFactory
{
private:
	LoginManager m_loginManager;

public:
	LoginManager& getLoginManager() { return this->m_loginManager; }
	LoginRequestHandler* createLoginRequestHandler();//return new LoginRequestHandler(m_loginManager); }
};

