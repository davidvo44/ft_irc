
#include "ft_irc.hpp"
#include "Server.hpp"
#include "Poll.hpp"

int main (int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Invalid Format, need './ircserv <port> <password>'" << std::endl;
		return 1;
	}
	TRY(
	Server launch(argv[1], argv[2]);

	Poll poll(&launch);
	poll.Start();
	return 0;
	)
}
