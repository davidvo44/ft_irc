/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:14 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/26 14:35:38 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

static void write_channel(Client client, Message message, Server &server);

void Command::JoinChannel(Client &client, Message message, Server &server)
{
	if (message.getTo().find('#') != 0 && message.getTo().find('&') != 0)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTo(), client.GetNick());
	std::map<std::string, Channel>::iterator it = server.getChannel().find(message.getTo());
	if (server.getChannel().empty() == false && it != server.getChannel().end())
	{
		it->second.JoinChannel(&client);
		std::cout << client.GetName() << " join " << message.getTo() << std::endl;
	}
	else
	{
		std::cout << "creating " << message.getTo() << std::endl;
		server.getChannel()[message.getTo()] = server.CreateChannel(&client, message.getTo());
	}
	write_channel(client, message, server);
}

static void write_channel(Client client, Message message, Server &server)
{
	//: Nick!User@Host JOIN #general
	std::map<int, Client *>::iterator itclient = server.getClients().begin();
	std::string response;

	while (itclient != server.getClients().end())
	{
		int fdcl = itclient->second->GetFd();
		response = Command::GetPrefix(client);
		response += "JOIN " + message.getTo() + "\n";
		send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		Command::getTopic(message, client, server);
		itclient++;
	}
}
