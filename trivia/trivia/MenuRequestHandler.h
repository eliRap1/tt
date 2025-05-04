#pragma once
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
class MenuRequestHandler : public IRequestHandler
{
private:
	LoggedUser m_loggedUser;
	RequestHandlerFactory& m_handlerFactory;

public:
	bool isRequestRelevant(RequestInfo& request) override;
	RequestResult handleRequest(RequestInfo& request) override;
};

