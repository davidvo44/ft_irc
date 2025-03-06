
#include "Command.hpp"

void Command::Topic(Message& message, Client &sender, Server &server)
{
	message.parsePRIVMSG_PART_TOPIC();

	std::cout << "suffix : " << message.getSuffix() << std::endl;
	std::cout << "CMD : " << message.getCommand() << std::endl;
	std::cout << "target : " << message.getTarget() << std::endl;
	std::cout << "param : " << message.getParameter() << std::endl;

	Channel *chan = server.getChannel().findValue(message.getTarget());
	if (message.getTarget() == "ft_irc")
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getCommand(), sender.getNick());
    if (!chan)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTarget(), sender.getNick());
	if (!chan->getClient().findValue(sender.getFd()))
		throw ProtocolError(ERR_NOTONCHANNEL, message.getTarget(), sender.getNick());
	if (message.getParameter().empty() == true)
		getTopic(message , sender, *chan);
	else
		chan->setTopic(message.getParameter());
}

void Command::getTopic(Message& message, Client &sender, Channel &chan)
{
	if (chan.getTopic().empty() == true)
		RplMessage::GetRply(RPL_NOTOPIC, sender.getFd(), 2, sender.getNick().c_str(), message.getTarget().c_str());
	else
		RplMessage::GetRply(RPL_TOPIC, sender.getFd(), 3, sender.getNick().c_str()\
		, message.getTarget().c_str(), chan.getTopic().c_str());
}
