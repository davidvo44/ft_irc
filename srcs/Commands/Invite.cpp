
#include "Command.hpp"
#include "Channel.hpp"

static void	addTargetToChannelClientList(Message& message, Client& source, Server &server, Channel &channel, std::string targetNick);

void Command::Invite(Message &message, Client &source, Server &server)
{
	std::cout << "INVITE cmd :" << std::endl;

	message.parseINVITE();

	std::string targetNick = message.getParameter();

	if (source.getLogStep() != 3)
		throw ProtocolError(ERR_NOTREGISTERED, source.getNick(), source.getNick());

	Channel *channel = server.getChannel().findValue(message.getTarget());
	if (!channel)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTarget(), source.getNick());

	Client	*sourceClient = channel->getClient().findValue(source.getFd());
	if (!sourceClient)
		throw ProtocolError(ERR_NOTONCHANNEL, message.getTarget(), source.getNick());

	if ((channel->viewMode('i')))
		if (channel->isOperator(source.getFd()) == false)
			throw ProtocolError(ERR_CHANOPRIVSNEEDED, message.getTarget(), source.getNick());

	std::map<int, Client *>::iterator target_it = channel->getClient().begin();
	for (; target_it != channel->getClient().end(); target_it++)
		if ((*target_it->second).getNick() == targetNick)
			throw ProtocolError(ERR_USERONCHANNEL, message.getTarget(), targetNick);

	addTargetToChannelClientList(message, source, server, *channel, targetNick);
}

void	addTargetToChannelClientList( Message &message, Client& source, Server &server, Channel &channel, std::string targetNick)
{
	std::string response;
	for (unsigned int i = 0; server[i]; ++i)
	{
		if (server[i]->getNick() == targetNick)
		{
			channel.addToWhitelist(server[i]->getFd());
			response = RPL_INVITING(source.getNick(), targetNick, message.getTarget());
			send(server[i]->getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
			break;
		}
	}
}
