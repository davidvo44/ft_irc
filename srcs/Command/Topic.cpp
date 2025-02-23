#include "Command.hpp"

static void setTopic(Message message, Client &sender, Server &server);

void Command::Topic(Message message, Client &sender, Server &server)
{
	if (message.getContent().empty() == true)
		getTopic(message , sender, server);
	else
		setTopic(message, sender, server);
}

void Command::getTopic(Message message, Client &sender, Server &server)
{
	std::map<std::string, Channel>::iterator it = server.getChannel().find(message.getTo());
	if (message.getTo() == "ft_irc")
		throw ProtocolError(461, message.getCommand(), sender.GetNick());
    if (it == server.getChannel().end())
		throw ProtocolError(403, message.getTo(), sender.GetNick());
	std::map<int, Client*>::iterator itcl = (it->second).GetClient().find(sender.GetFd());
	if (itcl == (it->second).GetClient().end())
		throw ProtocolError(442, message.getTo(), sender.GetNick());
	if (it->second.getTopic().empty() == true)
		RplMessage::GetRply(331, sender.GetFd(), 2, sender.GetNick().c_str(), message.getTo().c_str());
	else
		RplMessage::GetRply(332, sender.GetFd(), 3, sender.GetNick().c_str(), message.getTo().c_str(), it->second.getTopic().c_str());
}

static void setTopic(Message message, Client &sender, Server &server)
{
	std::map<std::string, Channel>::iterator it = server.getChannel().find(message.getTo());
	if (message.getTo() == "ft_irc")
		throw ProtocolError(461, message.getCommand(), sender.GetNick());
    if (it == server.getChannel().end())
		throw ProtocolError(403, message.getTo(), sender.GetNick());
	std::map<int, Client*>::iterator itcl = (it->second).GetClient().find(sender.GetFd());
	if (itcl == (it->second).GetClient().end())
		throw ProtocolError(442, message.getTo(), sender.GetNick());
	it->second.setTopic(message.getContent());
}