#include "Command.hpp"

void Command::WhoCommand(int FdCl, Client client, Message message, Server server)
{
	(void) server;
	Client clientChan;
	std::string response = ":irc.com 352 " + client.GetName() + " " + message.getContent() + " " +
                       clientChan.GetNick() + " " + clientChan.GetIpAdd() + " irc.com " +
                       clientChan.GetNick() + " H :1 " + clientChan.GetName() + "\r\n";
	send(FdCl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
// ERR_NOSUCHSERVER
//352 TonPseudo #general UserA host1 irc.net NickA H :0 RealNameA
//:server 352 <requesting_nick> <channel> <username> <host> <server> <nickname> <flags> :<hopcount> <realname>

}