/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:14 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/27 00:44:30 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "MutantMap.hpp"

static void checkmodechann(Client client, Channel &channel, Message message);
static void write_channel(Client &client, Message message, Server &server);

void Command::JoinChannel(Client &client, Message message, Server &server)
{
	if (message.getTo().find('#') != 0 && message.getTo().find('&') != 0)
		throw ProtocolError(ERR_BADCHANMASK, message.getTo(), client.GetNick());
	Channel *channel = server.getChannel().findValue(message.getTo());
	if (channel != NULL)
	{
		checkmodechann(client, *channel, message);
		channel->JoinChannel(&client);
		std::cout << client.GetName() << " join " << message.getTo() << std::endl;
	}
	else
	{
		std::cout << "creating " << message.getTo() << std::endl;
		server.getChannel()[message.getTo()] = server.CreateChannel(&client, message.getTo());
	}
	write_channel(client, message, server);
	Command::getTopic(message, client, server);
}

static void checkmodechann(Client client, Channel &channel, Message message)
{
	if (channel.viewMode('i') == true)
	{
		if (channel.IsWlist(client.GetFd()) == false)
			throw ProtocolError(ERR_CHANOPRIVSNEEDED, message.getTo(), client.GetNick());
	}
	if (channel.viewMode('k') == true)
	{
		if (message.getContent() != channel.getPassword())
			throw ProtocolError(ERR_BADCHANNELKEY, message.getTo(), client.GetNick());
	}
}

static void write_channel(Client &client, Message message, Server &server)
{
	//: Nick!User@Host JOIN #general
	std::map<int, Client *>::iterator itclient = server.getClients().begin();
	std::string response;

	while (itclient != server.getClients().end())
	{
		int fdcl = itclient->second->GetFd();
		response = client.GetPrefix();
		response += "JOIN " + message.getTo() + "\n";
		send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		itclient++;
	}
}
