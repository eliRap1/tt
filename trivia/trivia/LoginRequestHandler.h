#pragma once
#include "IRequestHandler.h"

#define LOGIN_CODE 101
#define SIGNUP_CODE 102
#define ERROR_CODE 999
class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler() {};
	RequestResult handleRequest(RequestInfo& request) override;
	bool isRequestRelevant(RequestInfo& request) override;
private:
};

