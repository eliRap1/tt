#include "Server.h"

int main()
{
	Server r;
	try
	{
		r.run();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}