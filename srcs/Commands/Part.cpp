/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:25 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/05 19:10:57 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::Part(Message& message, Client &sender, Server &server)
{
	message.parsePRIVMSG_PART_TOPIC();

	std::string	response;
	unsigned idx = 0;
	std::cout << "PART cmd :" << std::endl;
	Channel *channel = server.getChannel().findValue(message.getTarget());
	if (!channel)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTarget(), sender.getNick());
	if (!channel->getClient().findValue(sender.getFd()))
		throw ProtocolError(ERR_NOTONCHANNEL, message.getTarget(), sender.getNick());
	while ((*channel)[idx])
	{
		response = sender.getPrefix() + " PART " + message.getTarget() + " " + message.getParameter() + "\n";
		send((*channel)[idx]->getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		idx++;
	}
	channel->partChannel(sender);
}
