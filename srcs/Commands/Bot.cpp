#include "Command.hpp"

static void JoinBot(Server &server, Client &sender, Message &message)
{
	sockaddr_in servAddr = server.getServerAddr();
	socklen_t servAddrLen = sizeof(server.getServerAddr());
	pollfd newfd;
	int fdNewClient;

	fdNewClient = accept(server.getFd(), (struct sockaddr *)&servAddr, &servAddrLen);
	if (fdNewClient < 0)
		throw ExceptionError("Accept Fail");
	std::cout << "New client accepted : " << inet_ntoa(servAddr.sin_addr) << std::endl;
	newfd.events = POLLIN;
	newfd.fd = fdNewClient;
	newfd.revents = 0;
	server.setLogBot(true);
}