/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:28 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/27 18:21:01 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void PrivmsgUser(Message &message, Client &sender, Server &server);
void PrivmsgChan(Message &message, Client &sender, Channel &chan);

void Command::PrivateMessage(Message &message, Client &sender, Server &server)
{
	if (message.getTo().empty() == true)
		throw ProtocolError(ERR_NORECIPIENT, "", sender.GetNick());
	if (message.getContent().empty() == true)
		throw ProtocolError(ERR_NOTEXTTOSEND, "", sender.GetNick());
	if (message.getTo().find('#') != 0 && message.getTo().find('&') != 0)
	{
		PrivmsgUser(message, sender, server);
		return;
	}
	Channel *chan = server.getChannel().findValue(message.getTo());
	if (chan == NULL)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTo(), sender.GetNick());
	if (chan->GetClient().findValue(sender.GetFd()) == NULL)
		throw ProtocolError(ERR_CANNOTSENDTOCHAN, message.getTo(), sender.GetNick());
	PrivmsgChan(message, sender, *chan);
}

void PrivmsgUser(Message &message, Client &sender, Server &server)
{
	unsigned idx = 0;

	while (server[idx] != NULL)
	{
		if (server[idx]->GetName() == message.getTo())
			break;
		idx++;
	}
	if (server[idx] == NULL)
		throw ProtocolError(ERR_NOSUCHNICK, message.getTo(), sender.GetNick());
	std::string response;
	response = sender.GetPrefix() + "PRIVMSG " + message.getTo() + " " + message.getContent() + "\n";
	send(server[idx]->GetFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}

void PrivmsgChan(Message &message, Client &sender, Channel &chan)
{
	unsigned idx = 0;
	std::string response;
	while (chan[idx] != NULL)
	{
		if (chan[idx]->GetFd() == sender.GetFd())
		{
			idx++;
			continue;
		}
		response = sender.GetPrefix() + "PRIVMSG " + message.getTo() + " " + message.getContent() + "\n";
		send(chan[idx]->GetFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		idx++;
	}
}
