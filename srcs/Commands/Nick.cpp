/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:22 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/27 18:52:58 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::Nick(Message message, Client &sender, Server &server)
{
	std::string	response;
	unsigned idx = 0;

	if (message.getContent().empty() == true)
		throw ProtocolError(ERR_NONICKNAMEGIVEN, message.getContent(), sender.GetNick());
	if (message.getContent().find('#') == 0 ||  message.getContent().find('&') == 0 || message.getContent().find(';') == 0 || \
	message.getContent().find(" ") != std::string::npos)
		throw ProtocolError(ERR_ERRONEUSNICKNAME, message.getContent(), sender.GetNick());
	while (server[idx])
	{
		if (server[idx]->GetNick() == message.getContent())
			throw ProtocolError(ERR_NICKNAMEINUSE, message.getContent(), sender.GetNick());
		idx++;
	}
	response = sender.GetPrefix() + "NICK " + message.getContent() + "\n";
	SendBySharedChannels(response, sender, server);
	send(sender.GetFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	sender.SetNick(message.getContent());
}
