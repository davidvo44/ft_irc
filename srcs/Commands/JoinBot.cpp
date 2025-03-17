
#include "Command.hpp"
#include "Bot.hpp"

void Command::JoinBot(Server &server)
{
	std::cout << "Bot accepted : " << std::endl;
	int sock[2];
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sock) == -1)
	{
        throw("socket");
    }
	server.setBot(new Bot(sock[0], sock[1]));
	// server.AcceptNewClient();
	// Server::CheckNewClient(int fd, std::string IpAdd)
	// _Clients[sock[1]] = new Client(fd, IpAdd);
	server.setLogBot(true);
}
