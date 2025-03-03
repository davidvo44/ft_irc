/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:17 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/03 18:07:51 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Channel.hpp"
#include <sstream>

// INSERT REASON FOR KICK AND INSERT KICK MESSAGE (+ CREATE DEFAULT KICK MESSAGE IF NONE PROVIDED)

void Command::Kick(Message message, Client &opClient, Server &server)
{
	std::string	response;
	std::string	reasonForKick = "Inappropriate behaviour";
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
			if (!message.getPass().empty())
				reasonForKick = message.getPass();
			response = opClient.GetPrefix();
			response += " KICK " + message.getTo() + " " + targetClientNick + " " + reasonForKick + "\r\n";
			send((*client_it->second).GetFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
			channel->PartChannel((*client_it->second));
			break;
		}
	}
	opClient.SetNick(opClient.GetNick().erase(0, opClient.GetNick().find_first_not_of(" \n\r\v\f\t")));
	(*client_it->second).SetNick((*client_it->second).GetNick().erase(0, (*client_it->second).GetNick().find_first_not_of(" \n\r\v\f\t")));
	// std::string message2 = message.getTo();
	// message2.erase(0, message2.find_first_not_of(" \n\r\v\f\t"));
	std::string clientNick = opClient.GetNick() + " " + (*client_it->second).GetNick();
	if (client_it == channel->GetClient().end())
		throw ProtocolError(ERR_USERNOTINCHANNEL, message.getTo(), clientNick);

	client_it = channel->GetClient().begin();
	for (; client_it != channel->GetClient().end(); ++client_it)
		send((*client_it->second).GetFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}
