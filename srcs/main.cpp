
#include "ft_irc.hpp"
#include "Server.hpp"
#include "Poll.hpp"

Server* Server::_instance = NULL;

int main (int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Invalid Format, need './ircserv <port> <password>'" << std::endl;
		return 1;
	}
	TRY(
	Server *server = Server::getInstance(argv[1], argv[2]);
	Poll poll(server);
	poll.Start();
	return 0;
	)
}
