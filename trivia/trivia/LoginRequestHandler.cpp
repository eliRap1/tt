#include "LoginRequestHandler.h"

RequestResult LoginRequestHandler::handleRequest(RequestInfo& request)
{
	RequestResult result;

	if (request.id == LOGIN_CODE)
	{
		// Deserialize login request
		LoginRequest loginReq = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer);
		std::cout << "Login attempt by user: " << loginReq.username << std::endl;

		// For now always succeed (status = 1)
		LoginResponse response{ 1 };
		result.response = JsonResponsePacketSerializer::serializeLoginResponse(response);
	}
	else if (request.id == SIGNUP_CODE)
	{
		// Deserialize signup request
		SignupRequest signupReq = JsonRequestPacketDeserializer::deserializeSignupRequest(request.buffer);
		std::cout << "Signup attempt by user: " << signupReq.username << std::endl;

		// For now always succeed (status = 1)
		SignupResponse response{ 1 };
		result.response = JsonResponsePacketSerializer::serializeSignupResponse(response);
	}
	else
	{
		// Error - unknown request
		ErrorResponse error{ "Unknown request code." };
		result.response = JsonResponsePacketSerializer::serializeErrorResponse(error);
	}

	// Placeholder for the next handler – replace with actual logic later
	result.newHandler = nullptr;

	return result;
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo& request)
{
	return request.id == LOGIN_CODE || request.id == SIGNUP_CODE;
}

RequestResult LoginRequestHandler::login(RequestInfo& request)
{
	LoginRequest log;
	LoginStatus status;
	RequestResult res;
	log = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer);
	std::string username = log.username;
	std::string password = log.password;
	if (LoginStatus::Success == this->m_handlerFactory.getLoginManager().login(username, password))
	{
		LoginResponse response{ LOGIN_CODE };
		res.response = JsonResponsePacketSerializer::serializeLoginResponse(response);
		MenuRequestHandler* menuHandler = new MenuRequestHandler(); // Placeholder for the next handler – replace with actual logic late
		res.newHandler = menuHandler;
	}
	else
	{
		ErrorResponse error{ "Login failed" };
		res.response = JsonResponsePacketSerializer::serializeErrorResponse(error);
	}
	return res;
}

RequestResult LoginRequestHandler::signup(RequestInfo& request)
{

}