#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
	: m_database(database),
	m_loginManager(database),
	m_roomManager(),
	m_StatisticsManager(database)
{
}

IRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(const LoggedUser& user)
{
	return new MenuRequestHandler(user, *this);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_StatisticsManager;
}
