/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chess.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:57:09 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/04 18:43:48 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::ChessCommand(Server &server, Client &sender, Message &message)
{
	Channel *chan = server.getChannel().findValue(message.getTarget());
	if (chan == NULL)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getContent(), sender.getNick());
	if (message.getContent().empty() == true)
	{
		chan->getBot()->PrintChess(sender.getFd());
		return ;
	}
	if (message.getContent() == "join")
	{
		chan->getBot()->JoinChess(sender.getFd());
		return;
	}
	chan->getBot()->Ongame(sender.getFd(), message);
}
