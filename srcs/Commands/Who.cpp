/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:36 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/28 09:24:01 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::WhoCommand(int FdCl, Client &client, Message &message, Server &server)
{
	int idx = 0;
	std::string response;
	Channel *chan = server.getChannel().findValue(message.getContent());
	if (!chan)
	throw ProtocolError(ERR_NOSUCHCHANNEL, message.getContent(), client.GetNick());
	while ((*chan)[idx])
	{
		response = chan->getName() + " " + (*chan)[idx]->GetName() + " " + (*chan)[idx]->GetIpAdd() + " " \
		+ (*chan)[idx]->GetNick() + " H :0 " + (*chan)[idx]->GetName() + "\n";
		RplMessage::GetRply(RPL_WHOREPLY, FdCl, 2, client.GetNick().c_str(), response.c_str());
		idx++;
	}
	RplMessage::GetRply(RPL_ENDOFWHO, FdCl, 2, client.GetNick().c_str(), message.getContent().c_str());
	// Client clientChan;
	// std::string response = ":irc.com 352 " + client.GetName() + " " + message.getContent() + " " +
    //                    clientChan.GetNick() + " " + clientChan.GetIpAdd() + " irc.com " +
    //                    clientChan.GetNick() + " H :1 " + clientChan.GetName() + "\r\n";
	// send(FdCl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
// ERR_NOSUCHSERVER
//352 TonPseudo #general UserA host1 irc.net NickA H :0 RealNameA
//:server 352 <requesting_nick> <channel> <username> <host> <server> <nickname> <flags> :<hopcount> <realname>
// 352 thierry #general ~john example.com irc.example.com john H :0 John Doe
// 352 thierry #general ~alice example.net irc.example.com alice G :0 Alice Smith
// 315 thierry #general :End of WHO list

}
