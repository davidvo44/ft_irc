/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:22 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/04 18:30:54 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::Nick(Message message, Client &sender, Server &server)
{
	std::string	response;
	unsigned idx = 0;

	if (message.getContent().empty() == true)
		throw ProtocolError(ERR_NONICKNAMEGIVEN, message.getContent(), sender.getNick());
	if (message.getContent().find('#') == 0 ||  message.getContent().find('&') == 0 || message.getContent().find(';') == 0 || \
	message.getContent().find(" ") != std::string::npos)
		throw ProtocolError(ERR_ERRONEUSNICKNAME, message.getContent(), sender.getNick());
	while (server[idx])
	{
		if (server[idx]->getNick() == message.getContent())
			throw ProtocolError(ERR_NICKNAMEINUSE, message.getContent(), sender.getNick());
		idx++;
	}
	response = sender.getPrefix() + "NICK " + message.getContent() + "\n";
	SendBySharedChannels(response, sender, server);
	send(sender.getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	sender.setNick(message.getContent());
}
