
#include "Command.hpp"
#include "Bot.hpp"

void Command::JoinBot(Server &server, Client &sender)
{
	if (server.getBot())
		return;
	std::cout << "Bot accepted : " << std::endl;
	int sock[2];
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sock) == -1)
	{
        throw("socket");
    }
	std::string response = ":irc.com 002 " + sender.getName() + " :Bot added!!\r\nInvite ChessBot to your channel\r\n";
	send(sender.getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	server.CheckNewBot(sock);
}

