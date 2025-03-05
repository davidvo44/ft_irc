/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:22 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/05 18:38:48 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::Nick(Message& message, Client &sender, Server &server)
{
	std::string	response;
	unsigned idx = 0;

	if (message.getParameter().empty() == true)
		throw ProtocolError(ERR_NONICKNAMEGIVEN, message.getParameter(), sender.getNick());
	if (message.getParameter().find('#') == 0 ||  message.getParameter().find('&') == 0 || message.getParameter().find(';') == 0 || \
	message.getParameter().find(" ") != std::string::npos)
		throw ProtocolError(ERR_ERRONEUSNICKNAME, message.getParameter(), sender.getNick());
	while (server[idx])
	{
		if (server[idx]->getNick() == message.getParameter())
			throw ProtocolError(ERR_NICKNAMEINUSE, message.getParameter(), sender.getNick());
		idx++;
	}
	response = sender.getPrefix() + "NICK " + message.getParameter() + "\n";
	SendBySharedChannels(response, sender, server);
	send(sender.getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	sender.setNick(message.getParameter());
}
