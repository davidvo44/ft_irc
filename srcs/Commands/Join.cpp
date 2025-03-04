/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:14 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/04 18:44:54 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "MutantMap.hpp"

static void checkmodechann(Client client, Channel &channel, Message message);
static void write_channel(Client &client, Message message, Server &server);

void Command::joinChannel(Client &client, Message message, Server &server)
{
	if (message.getTarget().find('#') != 0 && message.getTarget().find('&') != 0)
		throw ProtocolError(ERR_BADCHANMASK, message.getTarget(), client.getNick());
	Channel *channel = server.getChannel().findValue(message.getTarget());
	if (channel != NULL)
	{
		checkmodechann(client, *channel, message);
		channel->joinChannel(&client);
		std::cout << client.getName() << " join " << message.getTarget() << std::endl;
	}
	else
	{
		std::cout << "creating " << message.getTarget() << std::endl;
		server.getChannel()[message.getTarget()] = server.CreateChannel(&client, message.getTarget());
		channel = server.getChannel().findValue(message.getTarget());
	}
	write_channel(client, message, server);
	Command::getTopic(message, client, *channel);
}

static void checkmodechann(Client client, Channel &channel, Message message)
{
	if (channel.viewMode('i') == true)
	{
		if (channel.isInWhitelist(client.getFd()) == false)
			throw ProtocolError(ERR_INVITEONLYCHAN, message.getTarget(), client.getNick());
	}
	if (channel.viewMode('k') == true)
	{
		if (message.getContent() != channel.getSuffixword())
			throw ProtocolError(ERR_BADCHANNELKEY, message.getTarget(), client.getNick());
	}
}

static void write_channel(Client &client, Message message, Server &server)
{
	std::string response;
	unsigned idx = 0;
	while (server[idx])
	{
		int fdcl = server[idx]->getFd();
		response = client.getPrefix() + "JOIN " + message.getTarget() + "\n";
		send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		idx++;
	}
}
