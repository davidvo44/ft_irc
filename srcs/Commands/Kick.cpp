
#include "Command.hpp"
#include "Channel.hpp"
#include <sstream>

static void searchTargetClient(Message &message, Channel &channel, Client &source);
static void sendKickMessageToAllClientsOnChannel(Channel &channel, std::string response);

void Command::Kick(Message& message, Client &source, Server &server)
{
	std::cout << "KICK cmd :" << std::endl;

	message.parseKICK();

	std::string targetNick = message.getParameter();

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

	if (targetNick.empty() == true)
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getCommand(), source.getNick());

	searchTargetClient(message, *channel, source);
}

void searchTargetClient(Message &message, Channel &channel, Client &source)
{
	std::string	response;
	std::string	reasonForKick = "Inappropriate behaviour";
	std::string targetNick = message.getParameter();
	unsigned int i = 0;

	while (channel[i])
	{
		if (channel[i]->getNick() == targetNick)
			break;
		i++;
	}

	std::string sourceNickPlusClientNick = source.getNick() + " " + targetNick;
	if (!channel[i])
		throw ProtocolError(ERR_USERNOTINCHANNEL, message.getTarget(), sourceNickPlusClientNick);

	reasonForKick = message.getSuffix();
	response = source.getPrefix();
	response += " KICK " + message.getTarget() + " " + targetNick + " " + reasonForKick + "\r\n";
	send(channel[i]->getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	channel.partChannel(*channel[i]);

	sendKickMessageToAllClientsOnChannel(channel, response);
}

void sendKickMessageToAllClientsOnChannel(Channel &channel, std::string response)
{
	for (unsigned int i = 0; channel[i]; i++)
		send(channel[i]->getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}
