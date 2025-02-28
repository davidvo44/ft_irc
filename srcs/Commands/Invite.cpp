/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:15:17 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/28 15:34:09 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
/*
	INVITE user to channel
	Parameter <nickname> is person to be invited on <channel>.

	Target channel SHOULD exist (at least one user is on it)
	Otherwise reject with ERR_NOSUCHCHANNEL

	Only channel members allowed to invite
	Otherwise MUST reject with ERR_NOTONCHANNEL

	Servers MAY reject with ERR_CHANOPRIVSNEEDED
	If channel has invite-only mode set and user is not operator

	If user already on channel, reject with ERR_USERONCHANNEL

	When invite is successful,
		send a RPL_INVITING to the command issuer,
		an INVITE message, with issuer as <source>, to the target user.
		Other channel members SHOULD NOT be notified.
*/
void	Command::Invite(Message message, Client &client, Server &server)
{

}
