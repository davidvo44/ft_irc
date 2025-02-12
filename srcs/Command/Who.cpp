#include "Command.hpp"

void Command::WhoCommand(int FdCl, Client client, Message message, Server server)
{
	(void) server;
	Client clientChan;
	write (FdCl, "352 ", 4);
	write (FdCl, client.GetName().c_str(), strlen(client.GetName().c_str()));
	write (FdCl, message.getContent().c_str(), strlen(message.getContent().c_str()));
	write (FdCl, clientChan.GetNick().c_str(), strlen(clientChan.GetNick().c_str()));
	write (FdCl, clientChan.GetIpAdd().c_str(), strlen(clientChan.GetIpAdd().c_str()));
	write (FdCl, clientChan.GetName().c_str(), strlen(clientChan.GetName().c_str()));

// ERR_NOSUCHSERVER
//352 TonPseudo #general UserA host1 irc.net NickA H :0 RealNameA
}