#include "./../header/ft_irc.hpp"
#include "./Server/Server.hpp"
#include "./Poll/Poll.hpp"

int main (void)
{
	TRY(
	Server launch;
		
	Poll poll(&launch);
	poll.Start();
	return 0;
	)
}