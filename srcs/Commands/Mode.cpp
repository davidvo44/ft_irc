/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:19 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/28 02:36:14 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

static void getMode(Client &sender, Channel &channel);
static Channel *parseMode(Message &message, Client &sender, Server &server);
static int CheckChar(char c, Message &message, Client &sender, Channel &channel);
static void setOpe(Client &sender, Channel &channel, char sign, Message &message);
static void setPass(Channel &channel, char sign, Message &message);

void Command::checkMode(Message message, Client &sender, Server &server)
{
	Channel *channel = parseMode(message, sender, server);
	if (message.getContent().empty() == true)
	{
		getMode(sender, *channel);
		return;
	}
	void (Channel::*functptr)(char s);
	if (message.getContent()[0] == '+')
		functptr = &Channel::addMode;
	else if (message.getContent()[0] == '-')
		functptr = &Channel::deleteMode;
	else
		throw ProtocolError(ERR_UNKNOWNMODE, message.getContent().erase(1), sender.GetNick());
	for (int i = 1; message.getContent()[i] != '\0'; i++)
	{
		if (CheckChar(message.getContent()[i], message, sender, *channel) == 0)
			(*channel.*functptr)(message.getContent()[i]);
	}
}

static void getMode(Client &sender, Channel &channel)
{
	// -i, -t, -k, -l
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
	RplMessage::GetRply(RPL_CHANNELMODEIS, sender.GetFd(), 3, sender.GetNick().c_str(), channel.getName().c_str(), reply.c_str());
}

static Channel *parseMode(Message &message, Client &sender, Server &server)
{
	if (message.getTo().empty() == true)
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getCommand(), sender.GetNick());
	Channel *channel = server.getChannel().findValue(message.getTo());
	if (channel == NULL)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTo(), sender.GetNick());
	if (channel->IsOperator(sender.GetFd()) == false)
		throw ProtocolError(ERR_CHANOPRIVSNEEDED, message.getTo(), sender.GetNick());
	if (message.getContent()[0] == '+' && message.getContent().find('o') != std::string::npos && \
	message.getContent().find('k') != std::string::npos)
	{
		std::string str = "o";
		throw ProtocolError(ERR_UNKNOWNMODE, str, sender.GetNick());
	}
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
		setPass(channel, message.getContent()[0], message);
	if (ichar == 4)
	{
		setOpe(sender, channel ,message.getContent()[0], message);
		return 1;
	}
	if (ichar == 5)
	{
		std::string str(1, c);
		throw ProtocolError(ERR_UNKNOWNMODE, str, sender.GetNick());
	}
	if (message.getContent()[0] == '+' && ichar == 2)
	{
		std::cout << "PASS IS:" << message.getPass() << std::endl;
		channel.setPassword(message.getPass());
	}
	return 0;
}

static void setOpe(Client &sender, Channel &channel, char sign, Message &message)
{
	unsigned idx = 0;
	std::string response;
	while (channel[idx])
	{
		if (channel[idx]->GetNick() == message.getPass())
			break;
		idx++;
	}
	if (!channel[idx])
		throw ProtocolError(ERR_NOSUCHNICK, message.getPass(), sender.GetNick());
	if (sign == '+')
		channel.getOperator().push_back(channel[idx]->GetFd());
	else
	{
		std::vector<int>::iterator it = std::find(channel.getOperator().begin(), channel.getOperator().end(), channel[idx]->GetFd());
    	if (it != channel.getOperator().end())
			channel.getOperator().erase(it);
		else
			return;
	}
	response = sender.GetPrefix() +" MODE " + channel.getName() + " " + sign + "o " + message.getPass();
	idx = 0;
	while (channel[idx])
	{
		send(channel[idx]->GetFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		idx++;
	}
}

static void setPass(Channel &channel, char sign, Message &message)
{
	if (message.getPass().empty() == true)
		return;
	if (sign == '+')
		channel.setPassword(message.getPass());
}