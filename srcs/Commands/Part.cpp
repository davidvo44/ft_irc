/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:25 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/27 18:52:47 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::Part(Message message, Client &sender, Server &server)
{
	std::string	response;
	unsigned idx = 0;
	std::cout << "PART cmd :" << std::endl;
	Channel *channel = server.getChannel().findValue(message.getTo());
	if (!channel)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTo(), sender.GetNick());
	if (!channel->GetClient().findValue(sender.GetFd()))
		throw ProtocolError(ERR_NOTONCHANNEL, message.getTo(), sender.GetNick());
	while ((*channel)[idx])
	{
		response = sender.GetPrefix() + " PART " + message.getTo() + " " + message.getContent() + "\n";
		send((*channel)[idx]->GetFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		idx++;
	}
	channel->PartChannel(sender);
}
