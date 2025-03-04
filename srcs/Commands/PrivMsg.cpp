/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:28 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/04 18:43:48 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void PrivmsgUser(Message &message, Client &sender, Server &server);
void PrivmsgChan(Message &message, Client &sender, Channel &chan);

void Command::PrivateMessage(Message &message, Client &sender, Server &server)
{
	if (message.getTarget().empty() == true)
		throw ProtocolError(ERR_NORECIPIENT, "", sender.getNick());
	if (message.getContent().empty() == true)
		throw ProtocolError(ERR_NOTEXTTOSEND, "", sender.getNick());
	if (message.getTarget().find('#') != 0 && message.getTarget().find('&') != 0)
	{
		PrivmsgUser(message, sender, server);
		return;
	}
	Channel *chan = server.getChannel().findValue(message.getTarget());
	if (chan == NULL)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTarget(), sender.getNick());
	if (chan->getClient().findValue(sender.getFd()) == NULL)
		throw ProtocolError(ERR_CANNOTSENDTOCHAN, message.getTarget(), sender.getNick());
	PrivmsgChan(message, sender, *chan);
}

void PrivmsgUser(Message &message, Client &sender, Server &server)
{
	unsigned idx = 0;

	while (server[idx] != NULL)
	{
		if (server[idx]->getName() == message.getTarget())
			break;
		idx++;
	}
	if (server[idx] == NULL)
		throw ProtocolError(ERR_NOSUCHNICK, message.getTarget(), sender.getNick());
	std::string response;
	response = sender.getPrefix() + "PRIVMSG " + message.getTarget() + " " + message.getContent() + "\n";
	send(server[idx]->getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}

void PrivmsgChan(Message &message, Client &sender, Channel &chan)
{
	unsigned idx = 0;
	std::string response;
	while (chan[idx] != NULL)
	{
		if (chan[idx]->getFd() == sender.getFd())
		{
			idx++;
			continue;
		}
		response = sender.getPrefix() + "PRIVMSG " + message.getTarget() + " " + message.getContent() + "\n";
		send(chan[idx]->getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		idx++;
	}
}
