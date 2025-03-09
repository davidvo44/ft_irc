
#include "Command.hpp"
#include "Channel.hpp"
#include <sstream>

void Command::Kick(Message& message, Client &source, Server &server)
{
	std::string	response;
	std::string	reasonForKick = "Inappropriate behaviour";
	std::cout << "KICK cmd :" << std::endl;

	message.parseKICK();
	std::string targetNick = message.getParameter();

	std::cout << message.getCommand() << " | " << message.getTarget() << " | "  << message.getParameter() << " | " << message.getSuffix();
	if (source.getLogStep() != 3)
		throw ProtocolError(ERR_NOTREGISTERED, source.getNick(), source.getNick());

	std::map<std::string, Channel*>::iterator channel_it = server.getChannel().find(message.getTarget());

	if (channel_it == server.getChannel().end())
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTarget(), source.getNick());
	Channel *channel = channel_it->second;

	std::map<int, Client*>::iterator source_it = channel->getClient().begin();
	for (; source_it != channel->getClient().end(); source_it++)
	{}
	if (source_it == channel->getClient().end())
		throw ProtocolError(ERR_NOTONCHANNEL, message.getTarget(), source.getNick());

	if (channel->isOperator(source.getFd()) == false)
		throw ProtocolError(ERR_CHANOPRIVSNEEDED, message.getTarget(), source.getNick());

	if (targetNick.empty() == true)
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getCommand(), source.getNick());

	std::map<int, Client*>::iterator client_it = channel->getClient().begin();
	for (; client_it != channel->getClient().end(); client_it++)
	{
		if ((*client_it->second).getNick() == targetNick)
		{
			if (!message.getSuffix().empty())
				reasonForKick = message.getSuffix();
			response = source.getPrefix();
			response += " KICK " + message.getTarget() + " " + targetNick + " " + reasonForKick + "\r\n";
			send((*client_it->second).getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
			channel->partChannel((*client_it->second));
			break;
		}
	}
	std::string sourceNickPlusClientNick = source.getNick() + " " + targetNick;
	if (client_it == channel->getClient().end())
		throw ProtocolError(ERR_USERNOTINCHANNEL, message.getTarget(), sourceNickPlusClientNick);

	client_it = channel->getClient().begin();
	for (; client_it != channel->getClient().end(); ++client_it)
		send((*client_it->second).getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}
