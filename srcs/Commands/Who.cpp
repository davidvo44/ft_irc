/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:36 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/04 23:14:43 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::WhoCommand(int FdCl, Client &client, Message &message, Server &server)
{
	int idx = 0;
	std::string nickList = "";
	std::string response;

	if (message.getContent().empty() == true)
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getContent(), client.getNick());
	Channel *chan = server.getChannel().findValue(message.getContent());
	if (!chan)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getCommand(), client.getNick());
    while ((*chan)[idx]) {
        std::string prefix = "";
        nickList += prefix + (*chan)[idx]->getNick() + " ";
        idx++;
    }
	RplMessage::GetRply(RPL_NAMREPLY, FdCl, 3, client.getNick().c_str(), chan->getName().c_str(), nickList.c_str());
	RplMessage::GetRply(RPL_ENDOFNAMES, FdCl, 2, client.getNick().c_str(), chan->getName().c_str());
}
