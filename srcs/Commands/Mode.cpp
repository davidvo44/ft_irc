
#include "Command.hpp"

static void getMode(Client &sender, Channel &channel);
static Channel *parseModeBuffer(Message &message, Client &sender, Server &server);
static int CheckChar(char c, Message &message, Client &sender, Channel &channel);
static void setOpe(Client &sender, Channel &channel, char sign, Message &message);
static void setPass(Channel &channel, char sign, Message &message);
static void setLimit(Channel &channel, char sign, Message &message, Client &sender);

void Command::checkMode(Message& message, Client &sender, Server &server)
{
	if (sender.getLogStep() != 3)
		throw ProtocolError(ERR_NOTREGISTERED, sender.getNick(), sender.getNick());
	message.parseMode();
	Channel *channel = parseModeBuffer(message, sender, server);
	if (message.getParameter().empty() == true)
	{
		getMode(sender, *channel);
		return;
	}
	void (Channel::*functptr)(char s);
	if (message.getParameter()[0] == '+')
		functptr = &Channel::addMode;
	else if (message.getParameter()[0] == '-')
		functptr = &Channel::deleteMode;
	else
		throw ProtocolError(ERR_UNKNOWNMODE, message.getParameter().erase(1), sender.getNick());
	for (int i = 1; message.getParameter()[i] != '\0'; i++)
	{
		if (CheckChar(message.getParameter()[i], message, sender, *channel) == 0)
			(*channel.*functptr)(message.getParameter()[i]);
	}
}

static void getMode(Client &sender, Channel &channel)
{
	std::string response;
	std::string reply = "+";
	char array[] = {'i', 't', 'k', 'l'};
	int i = 0;
	while (i < 4)
	{
		if ((channel.viewMode(array[i])) == true)
		{
			reply += array[i];
		}
		i++;
	}
	std::cout << reply.size() << std::endl;
	if (reply.size() == 1)
		reply = "";
	response = RPL_CHANNELMODEIS(sender.getNick(), channel.getName(), reply);
	send(sender.getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}

static Channel *parseModeBuffer(Message &message, Client &sender, Server &server)
{
	if (message.getTarget().empty() == true)
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getCommand(), sender.getNick());
	Channel *channel = server.getChannel().findValue(message.getTarget());
	if (channel == NULL)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTarget(), sender.getNick());
	if (channel->isOperator(sender.getFd()) == false)
		throw ProtocolError(ERR_CHANOPRIVSNEEDED, message.getTarget(), sender.getNick());
	if (message.getParameter()[0] == '+' && message.getParameter().find('o') != std::string::npos && \
	message.getParameter().find('k') != std::string::npos)
		throw ProtocolError(ERR_UNKNOWNMODE, message.getParameter(), sender.getNick());
	return (channel);
}

static int CheckChar(char c, Message &message, Client &sender, Channel &channel)
{
	char array[] = {'i', 't', 'k', 'l', 'o'};
	int ichar = 0;
	while (ichar != 5)
	{
		if (array[ichar] == c)
			break;
		ichar++;
	}
	if (ichar == 2)
		setPass(channel, message.getParameter()[0], message);
	if (ichar == 3)
		setLimit(channel, message.getParameter()[0], message, sender);
	if (ichar == 4)
	{
		setOpe(sender, channel ,message.getParameter()[0], message);
		return 1;
	}
	if (ichar == 5)
	{
		std::string str(1, c);
		throw ProtocolError(ERR_UNKNOWNMODE, str, sender.getNick());
	}
	if (message.getParameter()[0] == '+' && ichar == 2)
	{
		std::cout << "PASS IS:" << message.getSuffix() << std::endl;
		channel.setPassword(message.getSuffix());
	}
	return 0;
}

static void setOpe(Client &sender, Channel &channel, char sign, Message &message)
{
	unsigned idx = 0;
	std::string response;
	while (channel[idx])
	{
		if (channel[idx]->getNick() == message.getSuffix())
			break;
		idx++;
	}
	if (!channel[idx])
		throw ProtocolError(ERR_NOSUCHNICK, message.getSuffix(), sender.getNick());
	if (sign == '+')
	{
		channel.getOperator().push_back(channel[idx]->getFd());
		response = RPL_YOUROPER(channel[idx]->getName());
	}
	else
	{
		std::vector<int>::iterator it = std::find(channel.getOperator().begin(), channel.getOperator().end(), channel[idx]->getFd());
		if (it != channel.getOperator().end())
			channel.getOperator().erase(it);
		else
			return;
	}
	response = sender.getPrefix() + " MODE " + channel.getName() + " " + sign + "o " + message.getSuffix();
	idx = 0;
	while (channel[idx])
	{
		send(channel[idx]->getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		idx++;
	}
}

static void setPass(Channel &channel, char sign, Message &message)
{
	if (message.getSuffix().empty() == true)
		return;
	if (sign == '+')
		channel.setPassword(message.getSuffix());
}

static void setLimit(Channel &channel, char sign, Message &message, Client &sender)
{
	std::string max = message.getSuffix();
	std::stringstream stream(max);
	int maxIntFormat;

	if (sign == '-')
		return;
	if (message.getSuffix().empty() == true)
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getCommand() + " " +message.getParameter(), sender.getNick());
	stream >> maxIntFormat;
	if (stream.fail() || maxIntFormat < 1)
		throw ProtocolError(ERR_INVALIDMODEPARAM, message.getCommand() + " " +message.getParameter(), sender.getNick());
	channel.setMaxclient(maxIntFormat);
}