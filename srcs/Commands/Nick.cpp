/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:22 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/27 00:45:07 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::Nick(Message message, Client &sender, Server &server)
{
	int			fdcl;
	std::string	response;

	if (message.getContent().empty() == true)
		throw ProtocolError(431, message.getContent(), sender.GetNick());
	std::map<int, Client*>::iterator itcl = server.getClients().begin();
	for (;itcl != server.getClients().end(); itcl++)
	{
		if (itcl->second->GetNick() == message.getContent())
			throw ProtocolError(433, message.getContent(), sender.GetNick());
	}

	fdcl = sender.GetFd();
	response = sender.GetPrefix();
	response += "NICK " + message.getContent() + "\n";

	SendBySharedChannels(response, sender, server);

	send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	sender.SetNick(message.getContent());
}
