/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:17 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/28 08:56:19 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Channel.hpp"


// SEND MESSAGE TO HEXCHAT AND ALL CLIENTS ON CHANNEL
// HANDLE MULTIPLE CLIENTS TO KICK
// INSERT REASON FOR KICK
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
void Command::Kick(Message message, Client &client, Server &server)
{
	int client_fd;
	std::string response;
	std::cout << "KICK cmd :" << std::endl;
	server.getChannel().findValue(message.getTo());
	std::map<std::string, Channel*>::iterator channel_it = server.getChannel().find(message.getTo());
	Channel *channel = channel_it->second;
	if (channel_it == server.getChannel().end())
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTo(), client.GetNick());

	int	isOperator = channel_it->second->IsOperator(client.GetFd());
	if (isOperator == false)
		throw ProtocolError(ERR_CHANOPRIVSNEEDED, message.getTo(), client.GetNick());
	std::string clientOpWantsToKick = message.getContent();
	std::map<int, Client*>::iterator client_it = channel->GetClient().begin();
	for (; client_it != channel->GetClient().end(); client_it++)
	{
		if ((*client_it->second).GetNick() == clientOpWantsToKick)
		{
			// std::cout << ":" << client.GetNick() << "!" << client.GetName() << "@" << client.GetIpAdd() << " PART " << message.getTo() << " " << message.getContent() << std::endl;
			// client_fd = (*client_it->second).GetFd();
			// std::cout << client_fd << std::endl;
			// response = GetPrefix(client);
			// response += " KICK " + message.getTo() + " " + message.getContent() + "\r\n";
			// send(client_fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
			SendBySharedChannels(response, client, server);
			channel->PartChannel((*client_it->second));
			break;
		}
	}
	if (client_it == channel->GetClient().end())
		throw ProtocolError(ERR_USERNOTINCHANNEL, clientOpWantsToKick + " " + channel->getName(),  client.GetNick());

	client_it = channel->GetClient().begin();
	for (; client_it != channel->GetClient().end(); ++client_it)
	{
		client_fd = (*client_it->second).GetFd();
		response = client.GetPrefix();
		response += " KICK " + message.getTo() + " " + message.getContent() + "\r\n";
		send(client_fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	}
}
