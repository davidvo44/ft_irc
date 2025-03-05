/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:15:17 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/05 23:24:49 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Channel.hpp"
/*
	INVITE user to channel
	Parameter <nickname> is person to be invited on <channel>.

	When invite is successful,
		send a RPL_INVITING to the command issuer,
		send an INVITE message to target user, with issuer as <source>
		Other channel members SHOULD NOT be notified.

	If user tries to join and doesn't have invite
		they receive ERR_INVITEONLYCHAN (473) command fails

	CMD FORMAT:
	/invite <nickname> <channel>
*/
void Command::Invite(Message &message, Client &client, Server &server)
{
	std::cout << "INVITE cmd :" << std::endl;
	std::string targetClientNick = message.getParameter();

	Channel *channel = server.getChannel().findValue(message.getTarget());
	if (!channel)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTarget(), client.getNick());

	std::map<int, Client *>::iterator client_it = channel->getClient().begin();
	for (; client_it != channel->getClient().end(); client_it++)
	{
		if ((*client_it->second).getNick() == targetClientNick)
			throw ProtocolError(ERR_USERONCHANNEL, message.getTarget(), targetClientNick);
	}
	if (client_it == channel->getClient().end())
		throw ProtocolError(ERR_NOTONCHANNEL, message.getTarget(), client.getNick());

	if ((channel->viewMode('i')))
		if (channel->isOperator(client.getFd()) == false)
			throw ProtocolError(ERR_CHANOPRIVSNEEDED, message.getTarget(), client.getNick());

	// if (/* successful invite */)
	// {
	// channel->addToWhitelist(targetClientNick);
	// sendInviteNotifToTarget();
	// }
}

// unsigned int client_i = 0;
// while (channel[client_i] != NULL)
// {
// 	if ((channel[client_i].getClient()).getNick() == message.getParameter())
// 	client_i++;
// }
// TRIED THIS WAY BUT COULDN'T FIGURE OUT HOW TO GET TARGET CLIENT NICK
