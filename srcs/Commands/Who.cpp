/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:36 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/02 19:40:56 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::WhoCommand(int FdCl, Client &client, Message &message, Server &server)
{
	int idx = 0;
	std::string response;
	if (message.getContent().empty() == true)
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getContent(), client.GetNick());
	Channel *chan = server.getChannel().findValue(message.getContent());
	if (!chan)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getCommand(), client.GetNick());
	while ((*chan)[idx])
	{
		response = chan->getName() + " " + (*chan)[idx]->GetName() + " " + (*chan)[idx]->GetIpAdd() + " " \
		+ (*chan)[idx]->GetNick() + " H :0 " + (*chan)[idx]->GetName() + "\n";
		RplMessage::GetRply(RPL_WHOREPLY, FdCl, 2, client.GetNick().c_str(), response.c_str());
		idx++;
	}
	RplMessage::GetRply(RPL_ENDOFWHO, FdCl, 2, client.GetNick().c_str(), message.getContent().c_str());
}
