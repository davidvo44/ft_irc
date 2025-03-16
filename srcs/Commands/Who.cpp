
#include "Command.hpp"

void Command::WhoCommand(int FdCl, Client &client, Message &message, Server &server)
{
	int idx = 0;
	std::string nickList = "";
	std::string response;

	if (client.getLogStep() != 3)
		throw ProtocolError(ERR_NOTREGISTERED, client.getNick(), client.getNick());
	message.parseWHO();
	if (message.getTarget().empty() == true)
	throw ProtocolError(ERR_NEEDMOREPARAMS, message.getTarget(), client.getNick());
	Channel *chan = server.getChannel().findValue(message.getTarget());
	if (!chan)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getCommand(), client.getNick());
	if (!(*chan).getClient().findValue(client.getFd()))
		throw ProtocolError(ERR_NOTONCHANNEL, message.getTarget(), client.getNick());
	while ((*chan)[idx])
	{
		std::string prefix;
		if (chan->isOperator((*chan)[idx]->getFd()) == true)
			prefix = "@";
		else
			prefix = "";
		nickList += prefix + (*chan)[idx]->getNick() + " ";
		idx++;
	}
	response = RPL_NAMREPLY(client.getNick(), chan->getName(), "", nickList) + RPL_ENDOFNAMES(chan->getName());
	send(FdCl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}
