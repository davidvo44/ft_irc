/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:36 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/05 16:28:09 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::WhoCommand(int FdCl, Client &client, Message &message, Server &server)
{
	int idx = 0;
	std::string response;
	if (message.getParameter().empty() == true)
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getParameter(), client.getNick());
	Channel *chan = server.getChannel().findValue(message.getParameter());
	if (!chan)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getCommand(), client.getNick());
	while ((*chan)[idx])
	{
		response = chan->getName() + " " + (*chan)[idx]->getName() + " " + (*chan)[idx]->getIpAddr() + " " \
		+ (*chan)[idx]->getNick() + " H :0 " + (*chan)[idx]->getName() + "\n";
		RplMessage::GetRply(RPL_WHOREPLY, FdCl, 2, client.getNick().c_str(), response.c_str());
		idx++;
	}
	RplMessage::GetRply(RPL_ENDOFWHO, FdCl, 2, client.getNick().c_str(), message.getParameter().c_str());
}
