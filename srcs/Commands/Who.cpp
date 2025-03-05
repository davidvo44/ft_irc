/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:36 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/05 23:25:50 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::WhoCommand(int FdCl, Client &client, Message &message, Server &server)
{
	int idx = 0;
	std::string nickList = "";
	std::string response;

	if (message.getParameter().empty() == true)
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getParameter(), client.getNick());
	Channel *chan = server.getChannel().findValue(message.getParameter());
	if (!chan)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getCommand(), client.getNick());
    while ((*chan)[idx]) {
        std::string prefix = "";
        nickList += prefix + (*chan)[idx]->getNick() + " ";
        idx++;
    }
	RplMessage::GetRply(RPL_NAMREPLY, FdCl, 3, client.getNick().c_str(), chan->getName().c_str(), nickList.c_str());
	RplMessage::GetRply(RPL_ENDOFNAMES, FdCl, 2, client.getNick().c_str(), chan->getName().c_str());
	while ((*chan)[idx])
	{
		response = chan->getName() + " " + (*chan)[idx]->getName() + " " + (*chan)[idx]->getIpAddr() + " " \
		+ (*chan)[idx]->getNick() + " H :0 " + (*chan)[idx]->getName() + "\n";
		RplMessage::GetRply(RPL_WHOREPLY, FdCl, 2, client.getNick().c_str(), response.c_str());
		idx++;
	}
	RplMessage::GetRply(RPL_ENDOFWHO, FdCl, 2, client.getNick().c_str(), message.getParameter().c_str());
}
