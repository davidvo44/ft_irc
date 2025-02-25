/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:19 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/25 22:55:39 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

static void getMode(Client &sender, Channel &channel);

void Command::checkMode(Message message, Client &sender, Server &server)
{
	if (message.getTo().empty() == true)
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getCommand(), sender.GetNick());
	std::map<std::string, Channel>::iterator it = server.getChannel().find(message.getTo());
	if (it == server.getChannel().end())
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTo(), sender.GetNick());
	if (it->second.IsOperator(sender.GetFd()) == false)
		throw ProtocolError(ERR_CHANOPRIVSNEEDED, message.getTo(), sender.GetNick());
	if (message.getContent().empty() == true)
	{
		getMode(sender, it->second);
		return;
	}
	void (Channel::*functptr)(char s);
	if (message.getContent()[0] == '+')
		functptr = &Channel::addMode;
	else if (message.getContent()[0] == '-')
		functptr = &Channel::deleteMode;
	else
	{
		functptr = NULL;
		throw ProtocolError(ERR_UNKNOWNMODE, message.getContent().erase(1), sender.GetNick());
	}
	char array[] = {'i', 't', 'k', 'l'};
	for (int i = 1; message.getContent()[i] != '\0'; i++)
	{
		int ichar = 0;
		while (ichar != 4)
		{
			if (array[ichar] == message.getContent()[i])
				break;
			ichar++;
		}
		if (ichar == 4)
		{
			message.getContent().erase(i + 1);
			message.getContent().erase(0, i);
			throw ProtocolError(ERR_UNKNOWNMODE, message.getContent(), sender.GetNick());
		}
		if (message.getContent()[0] == '+' && ichar == 2)
		{
			std::cout << "PASS IS:" << message.getContent() << std::endl;
			it->second.setPassword(message.getPass());
		}
		(it->second.*functptr)(message.getContent()[i]);
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
