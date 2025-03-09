
#include "Command.hpp"
#include "Channel.hpp"
#include <sstream>

// INSERT REASON FOR KICK AND INSERT KICK MESSAGE (+ CREATE DEFAULT KICK MESSAGE IF NONE PROVIDED)

void Command::Kick(Message& message, Client &opClient, Server &server)
{
	std::string	response;
	std::string	reasonForKick = "Inappropriate behaviour";
	std::cout << "KICK cmd :" << std::endl;
	std::string targetClientNick = message.getParameter();

	if (opClient.getLogStep() != 3)
		throw ProtocolError(ERR_NOTREGISTERED, opClient.getNick(), opClient.getNick());
	std::map<std::string, Channel*>::iterator channel_it = server.getChannel().find(message.getTarget());
	Channel *channel = channel_it->second;

	if (channel_it->second->isOperator(opClient.getFd()) == false)
		throw ProtocolError(ERR_CHANOPRIVSNEEDED, message.getTarget(), opClient.getNick());

	if (targetClientNick.empty())
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getTarget(), opClient.getNick());

	std::map<int, Client*>::iterator client_it = channel->getClient().begin();
	for (; client_it != channel->getClient().end(); client_it++)
	{
		if ((*client_it->second).getNick() == targetClientNick)
		{
			if (!message.getSuffix().empty())
				reasonForKick = message.getSuffix();
			response = opClient.getPrefix();
			response += " KICK " + message.getTarget() + " " + targetClientNick + " " + reasonForKick + "\r\n";
			send((*client_it->second).getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
			channel->partChannel((*client_it->second));
			break;
		}
	}
	opClient.setNick(opClient.getNick().erase(0, opClient.getNick().find_first_not_of(" \n\r\v\f\t")));
	(*client_it->second).setNick((*client_it->second).getNick().erase(0, (*client_it->second).getNick().find_first_not_of(" \n\r\v\f\t")));
	// std::string message2 = message.getTarget();
	// message2.erase(0, message2.find_first_not_of(" \n\r\v\f\t"));
	std::string clientNick = opClient.getNick() + " " + (*client_it->second).getNick();
	if (client_it == channel->getClient().end())
		throw ProtocolError(ERR_USERNOTINCHANNEL, message.getTarget(), clientNick);

	client_it = channel->getClient().begin();
	for (; client_it != channel->getClient().end(); ++client_it)
		send((*client_it->second).getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}
