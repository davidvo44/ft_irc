/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:17 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/25 18:18:19 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Channel.hpp"

// check si l'user est l'ope
// check si l'utilisateur d'en face existe
// s'aider de la commade part

void Command::Kick(Message message, Client &client, Server &server)
{
	std::cout << "KICK cmd :" << std::endl;
	std::map<std::string, Channel>::iterator channel_it = server.getChannel().find(message.getTo());
	Channel channel = channel_it->second;
	if (channel_it == server.getChannel().end())
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTo(), client.GetNick());
	std::map<int, Client*>::iterator toBeKicked_it = channel.GetClient().begin();

	for (; toBeKicked_it != channel.GetClient().end(); toBeKicked_it++)
		if ((*toBeKicked_it->second).GetNick() == message.getContent())
			break;
	if (toBeKicked_it == channel.GetClient().end())
		throw ProtocolError(ERR_USERNOTINCHANNEL, message.getContent() + " " + channel.getName(),  client.GetNick());
	if (channel_it->second.IsOperator(client.GetFd()) == false)
		throw ProtocolError(ERR_CHANOPRIVSNEEDED, message.getTo(), client.GetNick());

	channel.PartChannel((*toBeKicked_it->second));
}
