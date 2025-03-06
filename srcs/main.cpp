
#include "ft_irc.hpp"
#include "Server.hpp"
#include "Poll.hpp"

int main (void)
{
	TRY(
	Server launch;

	Poll poll(&launch);
	poll.Start();
	return 0;
	)
}
