
#include "Command.hpp"

static void setTopic(Client &sender, Channel &chan, Message &message);

void Command::Topic(Message& message, Client &sender, Server &server)
{
	message.parsePRIVMSG_PART_TOPIC();
	if (sender.getLogStep() != 3)
		throw ProtocolError(ERR_NOTREGISTERED, sender.getNick(), sender.getNick());

	Channel *chan = server.getChannel().findValue(message.getTarget());
	if (message.getTarget() == "ft_irc" || message.getTarget().empty())
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getCommand(), sender.getNick());
	if (!chan)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTarget(), sender.getNick());
	if (!chan->getClient().findValue(sender.getFd()))
		throw ProtocolError(ERR_NOTONCHANNEL, message.getTarget(), sender.getNick());
	if (message.getParameter().empty() == true)
		getTopic(message , sender, *chan);
	else
		setTopic(sender, *chan, message);
}

void Command::getTopic(Message &message, Client &sender, Channel &chan)
{
	std::string response;

	if (chan.getTopic().empty() == true)
		response = RPL_NOTOPIC(sender.getNick(), message.getTarget());
	else
		response = RPL_TOPIC(sender.getNick(), message.getTarget(), chan.getTopic());
	send(sender.getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}

static void setTopic(Client &sender, Channel &chan, Message &message)
{
	if (chan.viewMode('t') == true)
	{
		if (chan.isOperator(sender.getFd()) == false)
			throw ProtocolError(ERR_CHANOPRIVSNEEDED, message.getTarget(), sender.getNick());
	}
	chan.setTopic(message.getParameter());
}
