#include "Server.h"

void Server::run()
{
	std::string input;
	std::thread th(&Communicator::startHandleRequests, &m_communicator);
	th.detach();
	while (input != "exit")
	{
		std::cin >> input;
	}

}