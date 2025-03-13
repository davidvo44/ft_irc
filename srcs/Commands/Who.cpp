
#include "Command.hpp"

void Command::WhoCommand(int FdCl, Client &client, Message &message, Server &server)
{
	int idx = 0;
	std::string nickList = "";
	std::string response;

	message.parseWHO();
	if (message.getTarget().empty() == true)
	throw ProtocolError(ERR_NEEDMOREPARAMS, message.getTarget(), client.getNick());
	Channel *chan = server.getChannel().findValue(message.getTarget());
	if (!chan)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getCommand(), client.getNick());
	while ((*chan)[idx])
	{
		std::string prefix = "";
		nickList += prefix + (*chan)[idx]->getNick() + " ";
		idx++;
	}
	response = RPL_NAMREPLY(client.getNick(), chan->getName(), "", nickList) + RPL_ENDOFNAMES(chan->getName());
	send(FdCl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}

// void Command::WhoCommand(int FdCl, Client &client, Message &message, Server &server)
// {
// 	int idx = 0;
// 	std::string nickList = "";
// 	std::string response;

// 	if (client.getLogStep() != 3)
// 		throw ProtocolError(ERR_NOTREGISTERED, client.getNick(), client.getNick());
// 	message.parseWHO();
// 	if (message.getTarget().empty() == true)
// 		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getTarget(), client.getNick());
// 	Channel *chan = server.getChannel().findValue(message.getTarget());
// 	if (!chan)
// 		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getCommand(), client.getNick());
// 	while ((*chan)[idx]) {
// 		std::string prefix = "";
// 		nickList += prefix + (*chan)[idx]->getNick() + " ";
// 		idx++;
// 	}
// 	RplMessage::GetRply(RPL_NAMREPLY, FdCl, 3, client.getNick().c_str(), chan->getName().c_str(), nickList.c_str());
// 	RplMessage::GetRply(RPL_ENDOFNAMES, FdCl, 2, client.getNick().c_str(), chan->getName().c_str());
// 	while ((*chan)[idx])
// 	{
// 		response = chan->getName() + " " + (*chan)[idx]->getName() + " " + (*chan)[idx]->getIpAddr() + " " \
// 		+ (*chan)[idx]->getNick() + " H :0 " + (*chan)[idx]->getName() + "\n";
// 		RplMessage::GetRply(RPL_WHOREPLY, FdCl, 2, client.getNick().c_str(), response.c_str());
// 		idx++;
// 	}
// 	RplMessage::GetRply(RPL_ENDOFWHO, FdCl, 2, client.getNick().c_str(), message.getTarget().c_str());
// }
