/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:15:17 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/03 16:52:01 by saperrie         ###   ########.fr       */
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
void	Command::Invite(Message message, Client &client, Server &server)
{
	std::cout << "INVITE cmd :" << std::endl;
	std::string targetClientNick = message.getContent();

	Channel *channel = server.getChannel().findValue(message.getTo());
	if (!channel)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTo(), client.GetNick());

	std::map<int, Client*>::iterator client_it = channel->GetClient().begin();
	for (; client_it != channel->GetClient().end(); client_it++)
	{
		if ((*client_it->second).GetNick() == targetClientNick)
			throw ProtocolError(ERR_USERONCHANNEL, message.getTo(), targetClientNick);
	}
	if (client_it == channel->GetClient().end())
		throw ProtocolError(ERR_NOTONCHANNEL, message.getTo(), client.GetNick());

	if ((channel->viewMode('i')))
		if (channel->IsOperator(client.GetFd()) == false)
			throw ProtocolError(ERR_CHANOPRIVSNEEDED, message.getTo(), client.GetNick());

	// if (/* successful invite */)
	// {
	channel->addToWhitelist(targetClientNick);
		// sendInviteNotifToTarget();
	// }
}

// unsigned int client_i = 0;
// while (channel[client_i] != NULL)
// {
// 	if ((channel[client_i].GetClient()).getNick() == message.getContent())
// 	client_i++;
// }
// TRIED THIS WAY BUT COULDN'T FIGURE OUT HOW TO GET TARGET CLIENT NICK
