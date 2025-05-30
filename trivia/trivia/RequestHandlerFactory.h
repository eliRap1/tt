#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "StatisticsManager.h"
#include "RoomManager.h"
//#include "MenuRequestHandler.h"
class MenuRequestHandler;
class LoginRequestHandler;
class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);

	IRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(const LoggedUser& user);

	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticsManager();

private:
	IDatabase* m_database;
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	StatisticsManager m_StatisticsManager;
};