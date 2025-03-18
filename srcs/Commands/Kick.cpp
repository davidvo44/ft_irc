
#include "Command.hpp"
#include "Channel.hpp"
#include <sstream>

static void searchTargetAndKick(Message &message, Channel &channel, Client &source, std::string targetToKick);
static void sendKickMessageToAllClientsOnChannel(Channel &channel, std::string response);

void Command::Kick(Message& message, Client &source, Server &server)
{
	std::cout << "KICK cmd :" << std::endl;

	message.parseKICK();

	std::string allClientsToKick = message.getParameter();

	if (source.getLogStep() != 3)
		throw ProtocolError(ERR_NOTREGISTERED, source.getNick(), source.getNick());

	Channel *channel = server.getChannel().findValue(message.getTarget());
	if (!channel)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTarget(), source.getNick());

	Client	*sourceClient = channel->getClient().findValue(source.getFd());
	if (!sourceClient)
		throw ProtocolError(ERR_NOTONCHANNEL, message.getTarget(), source.getNick());

	if (channel->isOperator(source.getFd()) == false)
		throw ProtocolError(ERR_CHANOPRIVSNEEDED, message.getTarget(), source.getNick());

	if (allClientsToKick.empty() == true)
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getCommand(), source.getNick());

	std::string singleClientToKick;
	std::istringstream issClientsToKick(allClientsToKick);
	while (std::getline(issClientsToKick, singleClientToKick, ','))
	{
		if (!singleClientToKick.empty())
			searchTargetAndKick(message, *channel, source, singleClientToKick);
	}
}

void searchTargetAndKick(Message &message, Channel &channel, Client &source, std::string clientToKick)
{
	std::string	response;
	std::string	reasonForKick = "Inappropriate behaviour";
	std::string sourceNickPlusClientNick = source.getNick() + " " + clientToKick;
	unsigned int i = 0;

	Client* targetClient = NULL;
	while (channel[i])
	{
		if (channel[i]->getNick() == clientToKick)
		{
			targetClient = channel[i];
			break;
		}
		i++;
	}
	if (!targetClient)
		throw ProtocolError(ERR_USERNOTINCHANNEL, message.getTarget(), sourceNickPlusClientNick);

	reasonForKick = message.getSuffix();
	response = source.getPrefix();
	response += " KICK " + message.getTarget() + " " + clientToKick + " " + reasonForKick + "\r\n";
	send(targetClient->getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	channel.partChannel(*targetClient);

	sendKickMessageToAllClientsOnChannel(channel, response);
}

void sendKickMessageToAllClientsOnChannel(Channel &channel, std::string response)
{
	for (unsigned int i = 0; channel[i]; i++)
		send(channel[i]->getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}
