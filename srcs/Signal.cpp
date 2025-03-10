#include "Server.hpp"

static int serverSocket = -1;

static void signalHandler(int signum)
{
	if (signum == SIGINT)
	{
		std::cout << "\nServer closed" << std::endl;
		if (serverSocket != -1)
			close(serverSocket);
		Server::freeCloseAll();
		throw ExceptionError("SIGINT");
	}
}