#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_loginManager(database)
{

}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager; 
}

IRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser& loggedUser)
{
    return nullptr;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    // TODO: insert return statement here
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    // TODO: insert return statement here
}
