/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:17 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/28 17:06:19 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Channel.hpp"

/*
	std::map<std::string, Channel*>::iterator channel_it = server.getChannel().find(message.getTo());
	Channel *channel = channel_it->second;
	peut etre remplace par:
	Channel *channel = server.getChannel().findValue(message.getTo());


	if (channel_it == server.getChannel().end())
	peut etre remplace par:
	if (!channel)


	std::map<int, Client*>::iterator client_it = channel->GetClient().begin();
	for (; client_it != channel->GetClient().end(); client_it++)
	{}
	peut etre remplace par:
	unsigned idx = 0;
	while (channel[idx])
	{
	idx++
	}

*/

// INSERT REASON FOR KICK AND INSERT KICK MESSAGE (+ CREATE DEFAULT KICK MESSAGE IF NONE PROVIDED)

static void	notifyAllClientsTargetWasKicked(Client &client, std::map<int, Client*>::iterator client_it, Channel *channel, Server &server, std::string response);

void Command::Kick(Message message, Client &opClient, Server &server)
{
	std::string	response;
	std::cout << "KICK cmd :" << std::endl;
	std::string targetClientNick = message.getContent();

	std::map<std::string, Channel*>::iterator channel_it = server.getChannel().find(message.getTo());
	Channel *channel = channel_it->second;

	if (channel_it->second->IsOperator(opClient.GetFd()) == false)
		throw ProtocolError(ERR_CHANOPRIVSNEEDED, message.getTo(), opClient.GetNick());

	if (targetClientNick.empty())
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getTo(), opClient.GetNick());

	std::map<int, Client*>::iterator client_it = channel->GetClient().begin();
	for (; client_it != channel->GetClient().end(); client_it++)
	{
		if ((*client_it->second).GetNick() == targetClientNick)
		{
			response = opClient.GetPrefix();
			response += " KICK " + message.getTo() + " " + targetClientNick + "\r\n";
			SendBySharedChannels(response, opClient, server);
			channel->PartChannel((*client_it->second));
			break;
		}
	}
	if (client_it == channel->GetClient().end())
		throw ProtocolError(ERR_USERNOTINCHANNEL, message.getTo(), targetClientNick);

	notifyAllClientsTargetWasKicked(opClient, channel->GetClient().begin(), channel, server, response);
}

void	notifyAllClientsTargetWasKicked(Client &client, std::map<int, Client*>::iterator client_it, Channel *channel, Server &server, std::string response)
{
	for (; client_it != channel->GetClient().end(); ++client_it)
	{
		Command::SendBySharedChannels(response, client, server);
		send((*client_it->second).GetFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	}
}
